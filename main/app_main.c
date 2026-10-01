#include <stdio.h>
#include "esp_sleep.h"
#include "packet.h"
#include "sensor_if.h"
#include "lora_if.h"
#include "node_config.h"
#include "power_manager.h"
#include "diagnostics.h"

void app_main(void){
 node_config_t cfg; sensor_data_t s; uint8_t raw[sizeof(telemetry_packet_t)];
 node_config_defaults(&cfg); sensor_if_init(); lora_if_init();
 printf("\n=== ESP32 LoRa Remote Industrial Sensor Node ===\n");
 if(esp_sleep_get_wakeup_cause()==ESP_SLEEP_WAKEUP_TIMER) printf("Wake: periodic timer\n");
 if(sensor_if_read(&s)!=0){printf("Sensor fault\n");power_manager_sleep(cfg.sample_period_s);return;}
 telemetry_packet_t p={LORA_PACKET_VERSION,cfg.node_id,1,s.temperature_c_x100,s.humidity_rh_x100,s.battery_mv,s.status_flags,0};
 size_t len=packet_encode(&p,raw,sizeof(raw)); uint16_t retries=0; int ack=-1;
 for(uint8_t attempt=0;attempt<=cfg.max_retries;attempt++){ if(attempt) retries++; if(lora_if_send(raw,len)==0 && lora_if_wait_ack(cfg.ack_timeout_ms)==0){ack=0;break;} }
 diagnostics_print(cfg.node_id,p.sequence,retries,p.status_flags);
 printf("TX=%s ACK=%s RETRIES=%u NEXT_WAKE=%lus\n",len?"OK":"FAIL",ack==0?"YES":"NO",(unsigned)retries,(unsigned long)cfg.sample_period_s);
 power_manager_sleep(cfg.sample_period_s);
}