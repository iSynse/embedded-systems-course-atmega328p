
#ifndef SWITCHES_H
#define SWITCHES_H

#include <stdint.h>
#include <stdbool.h>
#include "types.h"

void switches_init(void);


bool switches_update(void);


bool switches_is_upshift_pressed(void);
bool switches_is_downshift_pressed(void);


bool switches_is_button_pressed(uint8_t button_pin);

#endif