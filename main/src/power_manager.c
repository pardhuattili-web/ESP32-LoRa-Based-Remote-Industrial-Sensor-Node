#include "power_manager.h"
#include "esp_sleep.h"
void power_manager_sleep(uint32_t s){esp_sleep_enable_timer_wakeup((uint64_t)s*1000000ULL);esp_deep_sleep_start();}