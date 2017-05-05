#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

typedef enum
{
  PS_PREAMBLE_0 = 0,
  PS_PREAMBLE_1,
  PS_LENGTH,
  PS_PAYLOAD,
  PS_CSUM_0,
  PS_CSUM_1
} parser_state_t;

void parser_init();
uint8_t parser_process_byte(const uint8_t byte);
void parser_set_rx_pkt_fptr(void (*fptr)(const uint32_t, const uint8_t *));

#endif
