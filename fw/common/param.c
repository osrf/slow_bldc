#include <stdio.h>
#include <string.h>
#include "param.h"

struct param
{
  const char *n;  // name
  int t;  // type
  volatile void *p;  // pointer to value
};

#define MAX_PARAMS 100
static struct param params[MAX_PARAMS];
static uint32_t num_params = 0;

void param_init()
{
  num_params = 0;
  for (uint32_t i = 0; i < MAX_PARAMS; i++) {
    params[i].t = PARAM_TYPE_INVALID;
    params[i].n = NULL;
    params[i].p = NULL;
  }
}

uint32_t param_count()
{
  return num_params;
}

void param_add(const char *param_name,
    const param_type_t param_type, volatile void *param_ptr)
{
  if (num_params >= MAX_PARAMS) {
    printf("out of param storage; can't add param [%s]\n", param_name);
    return;  // no more room. sorry
  }
  params[num_params].n = param_name;
  params[num_params].t = param_type;
  params[num_params].p = param_ptr;
  num_params++;
}

const char *param_get_name(const uint32_t param_idx)
{
  if (param_idx >= num_params)
    return NULL;
  return params[param_idx].n;
}

param_type_t param_get_type(const uint32_t param_idx)
{
  if (param_idx >= num_params)
    return PARAM_TYPE_INVALID;
  return params[param_idx].t;
}

volatile void *param_get_ptr(const uint32_t param_idx)
{
  if (param_idx >= num_params)
    return NULL;
  return params[param_idx].p;
}

//void param_set_int(const char *param_name, const uint32_t value)

void param_set_float(const char *param_name, const float value)
{
  for (uint32_t i = 0; i < num_params; i++) {
    struct param *p = &params[i];
    if (p->t == PARAM_TYPE_FLOAT && !strcmp(p->n, param_name)) {
      *((float *)p->p) = value;
      break;
    }
  }
}
