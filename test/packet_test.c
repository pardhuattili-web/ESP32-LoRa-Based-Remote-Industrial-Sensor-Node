#include <assert.h>
#include <stdio.h>
#include "../main/include/packet.h"
int main(void){telemetry_packet_t p={1,0x1201,42,3125,5840,3710,0,0},q={0};uint8_t b[sizeof(p)];size_t n=packet_encode(&p,b,sizeof(b));assert(n==sizeof(p));assert(packet_decode(b,n,&q)==0);assert(q.node_id==p.node_id&&q.sequence==p.sequence);b[2]^=1;assert(packet_decode(b,n,&q)==-2);puts("packet tests: PASS");return 0;}