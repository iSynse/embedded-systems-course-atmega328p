#include "gear_control.h"

static Gear_t current_gear = GEAR_N;  // Start in N

void gear_control_init(void) {
    current_gear = GEAR_N;
}

Gear_t gear_upshift(void) {
    if (current_gear < GEAR_8) {
        current_gear++;
    }
    return current_gear;
}

Gear_t gear_downshift(void) {
    if (current_gear > GEAR_R) {
        current_gear--;
    }
    return current_gear;
}

Gear_t gear_get_current(void) {
    return current_gear;
}

uint8_t gear_get_display_value(void) {
    switch (current_gear) {
        case GEAR_P: return 0;
        case GEAR_R: return 10;  // Display "R"
        case GEAR_N: return 11;  // Display "N"
        default: return (uint8_t)(current_gear - GEAR_1 + 1);  // gear 1-8
    }
}