#pragma once
#include <stddef.h>
#include <stdint.h>
void lora_if_init(void);
int lora_if_send(const uint8_t *data,size_t len);
int lora_if_wait_ack(uint32_t timeout_ms);