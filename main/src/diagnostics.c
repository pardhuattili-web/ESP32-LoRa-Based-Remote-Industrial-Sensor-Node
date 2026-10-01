#include "diagnostics.h"
#include <stdio.h>
void diagnostics_print(uint16_t n,uint32_t s,uint16_t r,uint16_t st){printf("NODE=0x%04X SEQ=%lu RETRIES=%u FLAGS=0x%04X\n",n,(unsigned long)s,(unsigned)r,(unsigned)st);}