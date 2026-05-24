#ifndef SPEED_SIMULATION_H
#define SPEED_SIMULATION_H

#include <stdint.h>
#include "types.h"

void speed_sim_init(void);


void speed_sim_update(void);


uint16_t speed_sim_get_speed_kmh(void);


uint16_t speed_sim_get_rpm(void);


uint8_t speed_sim_get_rpm_percentage(void);


void speed_sim_set_speed(uint16_t speed_kmh);

#endif 