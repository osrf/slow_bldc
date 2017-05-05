#include <stdio.h>
#include "control.h"
#include "params.h"

static uint32_t g_encoder_offset = 123;

void control_init()
{
  printf("control_init()\n");
  params_add("encoder_offset", PARAM_TYPE_INT, &g_encoder_offset);
}

void control_tick()
{

}
