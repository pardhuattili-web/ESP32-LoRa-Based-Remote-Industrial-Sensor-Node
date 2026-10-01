#pragma once
#include <stdint.h>
typedef struct { int16_t temperature_c_x100; uint16_t humidity_rh_x100; uint16_t battery_mv; uint16_t status_flags; } sensor_data_t;
void sensor_if_init(void);
int sensor_if_read(sensor_data_t *data);