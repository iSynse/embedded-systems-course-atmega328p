#ifndef GEAR_CONTROL_H
#define GEAR_CONTROL_H

#include "types.h"


void gear_control_init(void);

Gear_t gear_upshift(void);

Gear_t gear_downshift(void);

Gear_t gear_get_current(void);


uint8_t gear_get_display_value(void);

#endif