#include <stdio.h>
#include <pthread.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>
#include "../include/platform.h"

int current_speed = 0;
pthread_mutex_t lock;

int main() {
    int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    struct ifreq ifr; strcpy(ifr.ifr_name, "vcan0"); ioctl(s, SIOCGIFINDEX, &ifr);
    struct sockaddr_can addr = {AF_CAN, ifr.ifr_ifindex};
    bind(s, (struct sockaddr *)&addr, sizeof(addr));

    pthread_mutex_init(&lock, NULL);
    pthread_t t_rx, t_logic;

    pthread_create(&t_rx, NULL, can_rx_thread, &s);
    pthread_create(&t_logic, NULL, logic_thread, &s);

    pthread_join(t_rx, NULL);
    pthread_join(t_logic, NULL);
    return 0;
}
