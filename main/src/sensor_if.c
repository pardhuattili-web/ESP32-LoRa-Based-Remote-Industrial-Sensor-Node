#include "sensor_if.h"
void sensor_if_init(void){}
int sensor_if_read(sensor_data_t*d){if(!d)return-1;d->temperature_c_x100=3125;d->humidity_rh_x100=5840;d->battery_mv=3710;d->status_flags=0;return 0;}