#ifndef RS485_H
#define RS485_H

#include <stdint.h>

void rs485_init();
void rs485_send_block(const uint8_t *buf, uint32_t len);
void rs485_tick();

#endif

