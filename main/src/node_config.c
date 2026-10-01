#include "node_config.h"
void node_config_defaults(node_config_t*c){if(!c)return;c->node_id=0x1201;c->sample_period_s=60;c->ack_timeout_ms=800;c->max_retries=3;}