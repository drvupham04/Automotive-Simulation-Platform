#ifndef PLATFORM_H
#define PLATFORM_H
#include <pthread.h>
#include <linux/can.h>

extern int current_speed;
extern pthread_mutex_t lock;

void* can_rx_thread(void* arg);
void* logic_thread(void* arg);
void check_anomaly(int speed);
void send_can_frame(int s, int id, unsigned char data[], int dlc);

#endif
