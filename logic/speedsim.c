#include "speed_simulation.h"
#include "gear_control.h"
#include <math.h>

#define MAX_RPM 15000
#define SIMULATION_TICK_MS 20

static uint16_t current_speed_kmh = 0;
static uint16_t current_rpm = 0;
static uint32_t last_update_time = 0;

static const uint16_t gear_max_speeds[] = {
    0,      // P: Park 
    50,     // R: Reverse
    0,      // N: Neutral 
    90,     // 1st: 90 km/h
    140,    // 2nd: 140 km/h
    180,    // 3rd: 180 km/h
    220,    // 4th: 220 km/h
    260,    // 5th: 260 km/h
    300,    // 6th: 300 km/h
    330,    // 7th: 330 km/h
    350,    // 8th: 350 km/h 
};

static const float gear_accel_factor[] = {
    0.0,    // P
    0.3,    // R
    0.0,    // N
    1.5,    // 1st 
    1.3,    // 2nd
    1.1,    // 3rd
    0.9,    // 4th
    0.7,    // 5th
    0.5,    // 6th
    0.3,    // 7th
    0.2,    // 8th 
};

void speed_sim_init(void) {
    current_speed_kmh = 0;
    current_rpm = 0;
}

void speed_sim_update(void) {
    Gear_t gear = gear_get_current();
    uint16_t max_speed = gear_max_speeds[(uint8_t)gear];
    float accel_factor = gear_accel_factor[(uint8_t)gear];
    
    if (current_speed_kmh < max_speed) {
        uint16_t acceleration = (uint16_t)(accel_factor * 5);
        if (current_speed_kmh + acceleration > max_speed) {
            current_speed_kmh = max_speed;
        } else {
            current_speed_kmh += acceleration;
        }
    } else if (current_speed_kmh > max_speed) {
        current_speed_kmh -= 2;
    }

    if (gear == GEAR_N) {
        current_speed_kmh = (current_speed_kmh * 95) / 100; 
    }
    
    if (max_speed > 0) {
        uint16_t rpm_per_kmh = (MAX_RPM / 10) / ((uint8_t)gear - GEAR_1 + 1 + 2);
        current_rpm = (current_speed_kmh * rpm_per_kmh) / 10;
    
        if (current_rpm > MAX_RPM) {
            current_rpm = MAX_RPM;
        }
    } else {
        current_rpm = 0;
    }
}

uint16_t speed_sim_get_speed_kmh(void) {
    return current_speed_kmh;
}

uint16_t speed_sim_get_rpm(void) {
    return current_rpm;
}

uint8_t speed_sim_get_rpm_percentage(void) {
    return (uint8_t)((current_rpm * 100) / MAX_RPM);
}

void speed_sim_set_speed(uint16_t speed_kmh) {
    current_speed_kmh = speed_kmh;
}