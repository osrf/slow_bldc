#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

void serial_init();
void serial_send_block(const uint8_t *buf, uint32_t len);
void serial_tick();

#endif

