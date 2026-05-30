#include "../include/platform.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

// keyboard
void set_keypress(void) {
    struct termios new_settings;
    tcgetattr(0, &new_settings);
    new_settings.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(0, TCSANOW, &new_settings);
}

void* logic_thread(void* arg) {
    int s = *(int*)arg;
    int speed = 0;
    int turn_signal = 0; 
    int blink_counter = 0;

    set_keypress(); // Kích hoạt chế độ đọc phím 

    printf("\n--- AUTOMOTIVE PLATFORM SẴN SÀNG ---\n");
    printf("Mũi tên lên: Tăng tốc | Trái/Phải: Xi nhan | Space: Tắt xi nhan\n\n");

    while(1) {
        pthread_mutex_lock(&lock);
        
        // 1. ĐỌC PHÍM MŨI TÊN 
        int bytes_waiting;
        ioctl(0, FIONREAD, &bytes_waiting);
        if (bytes_waiting > 0) {
            int ch = getchar();
            if (ch == 27) { // Bắt mã phím mũi tên
                getchar(); // bỏ '['
                switch(getchar()) {
                    case 'A': if(speed < 250) speed += 5; break; // Lên
                    case 'B': if(speed > 5) speed -= 5; break;   // Xuống 
                    case 'D': turn_signal = 1; break; // Trái
                    case 'C': turn_signal = 2; break; // Phải
                }
            } else if (ch == ' ') {
                turn_signal = 0; // Space để tắt
            }
        }

        // 2. QUÁN TÍNH
        if (speed > 0) speed -= 1; 

        // 3. TÍNH NĂNG lỗi hiện thị (+30km/h trên mặt đồng hồ)
        // Nếu muốn bỏ dấu // ở dòng dưới
        int display_speed = speed;
        // if (speed > 0) display_speed = speed + 30;

        // 4. GỬI GÓI TIN TỐC ĐỘ (ID: 0x244)
        unsigned char data_speed[8] = {0, 0, (unsigned char)display_speed, (unsigned char)display_speed, 0, 0, 0, 0};
        send_can_frame(s, 0x244, data_speed, 8);

        // 5. GỬI GÓI TIN XI NHAN (ID: 0x188)
        if (turn_signal != 0) {
            blink_counter++;
            unsigned char sig_val = (blink_counter % 40 < 20) ? turn_signal : 0;
            unsigned char data_signal[4] = {sig_val, 0, 0, 0};
            send_can_frame(s, 0x188, data_signal, 4);
        }

        // 6. MODULE CHẨN ĐOÁN LỖI 
        check_anomaly(display_speed);

        // 7. IN RA MÀN HÌNH
        printf("Speed: %3d km/h | Signal: %d \r", display_speed, turn_signal);
        fflush(stdout);

        pthread_mutex_unlock(&lock);
        usleep(20000); // Vòng lặp 20ms nguyên bản
    }
    return NULL;
}
