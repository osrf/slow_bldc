#ifndef ENC_H
#define ENC_H

#include <stdint.h>
#define ENC_COUNTS 16384

void enc_init();
uint16_t enc_poll();

#endif
