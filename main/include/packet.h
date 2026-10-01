#pragma once
#include <stddef.h>
#include <stdint.h>
#define LORA_PACKET_VERSION 1U
typedef struct __attribute__((packed)) { uint8_t version; uint16_t node_id; uint32_t sequence; int16_t temperature_c_x100; uint16_t humidity_rh_x100; uint16_t battery_mv; uint16_t status_flags; uint16_t crc16; } telemetry_packet_t;
uint16_t packet_crc16(const uint8_t *data,size_t len);
size_t packet_encode(const telemetry_packet_t *p,uint8_t *out,size_t n);
int packet_decode(const uint8_t *data,size_t len,telemetry_packet_t *out);