#pragma once
#include <stdint.h>
typedef struct { uint16_t node_id; uint32_t sample_period_s; uint32_t ack_timeout_ms; uint8_t max_retries; } node_config_t;
void node_config_defaults(node_config_t *cfg);