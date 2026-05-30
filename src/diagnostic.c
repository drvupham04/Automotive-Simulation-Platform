#include "../include/platform.h"
#include <stdio.h>

void check_anomaly(int speed) {
    if (speed > 80) printf("[WARNING] Quá tốc độ: %d km/h!\n", speed);
}
