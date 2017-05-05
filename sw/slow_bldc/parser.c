#include <stdio.h>
#include "parser.h"

#define PARSER_PKT_MAX_LEN 256
static parser_state_t g_parser_state = PS_PREAMBLE_0;
static uint32_t g_parser_expected_length = 0;
static uint32_t g_parser_pkt_wpos = 0;
static uint8_t  g_parser_pkt[PARSER_PKT_MAX_LEN] = {0};
static uint16_t g_parser_csum = 0, g_parser_rx_csum = 0;
static void (*g_parser_rx_pkt_fptr)(const uint32_t, const uint8_t *) = 0;

void parser_init()
{
  g_parser_state = PS_PREAMBLE_0;
}

void parser_set_rx_pkt_fptr(void (*fptr)(const uint32_t, const uint8_t *))
{
  g_parser_rx_pkt_fptr = fptr;
}

static void parser_csum_byte(const uint8_t b)
{
  g_parser_csum += b; // placeholder for now. replace with usb csum sometime
}

uint8_t parser_process_byte(const uint8_t b)
{
  // printf("rx 0x%02x state %d\n", (unsigned)b, (int)g_parser_state);
  switch (g_parser_state)
  {
    case PS_PREAMBLE_0:
      if (b == 0xbe)
        g_parser_state = PS_PREAMBLE_1;
      g_parser_csum = 0;
      break;
    case PS_PREAMBLE_1:
      if (b == 0xef)
        g_parser_state = PS_LENGTH;
      break;
    case PS_LENGTH:
      if (b > 0)
      {
        g_parser_expected_length = b;
        g_parser_pkt_wpos = 0;
        g_parser_state = PS_PAYLOAD;
        parser_csum_byte(b);
      }
      else
        g_parser_state = PS_PREAMBLE_0;
      break;
    case PS_PAYLOAD:
      g_parser_pkt[g_parser_pkt_wpos] = b;
      parser_csum_byte(b);
      // printf("  payload %d/%d\n",
      //     g_parser_pkt_wpos, g_parser_expected_length);
      if (g_parser_pkt_wpos == g_parser_expected_length - 1)
        g_parser_state = PS_CSUM_0;
      if (g_parser_pkt_wpos < PARSER_PKT_MAX_LEN - 1)
        g_parser_pkt_wpos++;
      break;
    case PS_CSUM_0:
      g_parser_state = PS_CSUM_1;
      g_parser_rx_csum = b;
      break;
    case PS_CSUM_1:
      g_parser_state = PS_PREAMBLE_0;
      g_parser_rx_csum |= (b << 8);
      if (g_parser_rx_csum == g_parser_csum) {
        // printf("  pkt ok\n");
        if (g_parser_rx_pkt_fptr)
          g_parser_rx_pkt_fptr(g_parser_expected_length, g_parser_pkt);
        return g_parser_pkt[0];
      }
      else {
        // printf("csum fail: 0x%0x != 0x%x\n",
        //     g_parser_csum, g_parser_rx_csum);
      }
      break;
    default:
      g_parser_state = PS_PREAMBLE_0;
  }
  return 0;
}
