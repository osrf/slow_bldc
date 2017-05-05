#ifndef RS485_H
#define RS485_H

#include <stdint.h>

void rs485_init();
void rs485_tick();
void rs485_tx(const uint32_t len, const uint8_t *data);

#endif

