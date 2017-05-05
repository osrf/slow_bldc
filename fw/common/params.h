#ifndef PARAMS_H
#define PARAMS_H

#include <stdint.h>

typedef enum
{ PARAM_TYPE_INVALID,
  PARAM_TYPE_INT,
  PARAM_TYPE_FLOAT } param_type_t;

void params_init();
uint32_t params_count();
void params_add(const char *param_name,
    const param_type_t param_type, volatile void *param_ptr);
const char *params_get_name(const uint32_t param_idx);
param_type_t params_get_type(const uint32_t param_idx);
volatile void *params_get_ptr(const uint32_t param_idx);

#endif
