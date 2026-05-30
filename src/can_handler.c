#include "../include/platform.h"
#include <string.h>
#include <unistd.h>

void send_can_frame(int s, int id, unsigned char data[], int dlc) {
    struct can_frame frame;
    memset(&frame, 0, sizeof(struct can_frame));
    frame.can_id = id; frame.can_dlc = dlc;
    memcpy(frame.data, data, dlc);
    write(s, &frame, sizeof(struct can_frame));
}

void* can_rx_thread(void* arg) { return NULL; }
