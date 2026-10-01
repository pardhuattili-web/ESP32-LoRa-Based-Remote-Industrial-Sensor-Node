#include "lora_if.h"
#include <stdio.h>
void lora_if_init(void){}
int lora_if_send(const uint8_t*d,size_t n){if(!d||!n)return-1;printf("LoRa TX: %u bytes (simulation)\n",(unsigned)n);return 0;}
int lora_if_wait_ack(uint32_t timeout_ms){(void)timeout_ms;printf("LoRa ACK: simulated\n");return 0;}