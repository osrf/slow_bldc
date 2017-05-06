#ifndef PARAM_H
#define PARAM_H

#include <stdint.h>

typedef enum
{ PARAM_TYPE_INVALID,
  PARAM_TYPE_INT,
  PARAM_TYPE_FLOAT } param_type_t;

void param_init();
uint32_t param_count();
void param_add(const char *param_name,
    const param_type_t param_type, volatile void *param_ptr);
const char *param_get_name(const uint32_t param_idx);
param_type_t param_get_type(const uint32_t param_idx);
volatile void *param_get_ptr(const uint32_t param_idx);
void param_set_float(const char *param_name, const float value);
void param_set_int(const char *param_name, const uint32_t value);

#endif
