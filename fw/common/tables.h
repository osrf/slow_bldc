#ifndef TABLES_H
#define TABLES_H

#include "enc.h"
#include "motor.h"
#define TABLE_LEN (ENC_COUNTS / MOTOR_POLE_PAIRS)
#define TABLE_120_DEG (TABLE_LEN / 3)
extern const float g_tables_sine[TABLE_LEN];
extern const float g_tables_motor_modulation[TABLE_LEN];

#endif
