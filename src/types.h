#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>


typedef enum {
    GEAR_P = 0,     // Park
    GEAR_R = 1,     // Reverse
    GEAR_N = 2,     // Neutral
    GEAR_1 = 3,     // Gear 1
    GEAR_2 = 4,
    GEAR_3 = 5,
    GEAR_4 = 6,
    GEAR_5 = 7,
    GEAR_6 = 8,
    GEAR_7 = 9,
    GEAR_8 = 10,    
} Gear_t;


typedef struct {
    Gear_t current_gear;
    uint16_t current_speed_kmh;     // Viteza in km/h (0-350)
    uint16_t current_rpm;           // RPM (0-15000)
    uint8_t rpm_percentage;         
    bool upshift_pressed;
    bool downshift_pressed;
    uint32_t last_gear_change_time; //delay 20ms pentru schimbarea vitezei
} SteeringWheel_State_t;


typedef struct {
    bool current_state;
    bool last_state;
    uint32_t last_change_time;
    uint16_t debounce_ms;
    bool is_pressed;          
} Switch_t;


typedef struct {
    int16_t position;               
    int8_t last_clk_state;
    int8_t last_dt_state;
    int16_t increment;              
} Encoder_t;

#endif // TYPES_H