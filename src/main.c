#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "config.h"
#include "types.h"
#include "drivers/ws2812/ws2812.h"
#include "drivers/max7219/max7219.h"
#include "drivers/input/switches.h"
#include "drivers/timer/timer0.h"
#include "logic/gear_control.h"
#include "logic/speed_simulation.h"

static SteeringWheel_State_t wheel_state = {
    .current_gear = GEAR_N,
    .current_speed_kmh = 0,
    .current_rpm = 0,
    .rpm_percentage = 0,
    .upshift_pressed = false,
    .downshift_pressed = false,
    .last_gear_change_time = 0,
};


static void update_rpm_display(uint8_t rpm_percent) {
 
    
    uint8_t led_count = (rpm_percent * WS2812_COUNT) / 100;
    
    RGB_Color_t off_color = {0, 0, 0};
    RGB_Color_t on_color;
    
    if (rpm_percent < 60) {
        on_color = (RGB_Color_t){0, 255, 0};  
    } else if (rpm_percent < 85) {
        on_color = (RGB_Color_t){255, 255, 0};  
    } else {
        on_color = (RGB_Color_t){255, 0, 0}; 
    }
    
    for (uint8_t i = 0; i < WS2812_COUNT; i++) {
        if (i < led_count) {
            ws2812_set_color(i, on_color);
        } else {
            ws2812_set_color(i, off_color);
        }
    }
    
    ws2812_update();
}


static void update_7seg_display(uint8_t gear, uint16_t speed) {

    
    max7219_display_gear_speed(gear, speed);
}

static void system_init(void) {
    // Initialize all systems
    ws2812_init();  // This also clears LEDs
    max7219_init();
    switches_init();
    gear_control_init();
    speed_sim_init();
    
    // Initialize Timer0 (this enables global interrupts via sei())
    Timer0_Init();
    
    // Display initial state - Gear N, Speed 0
    uint8_t initial_gear_display = gear_get_display_value();
    max7219_display_gear_speed(initial_gear_display, 0);
}

#define UPDATE_INTERVAL_MS 20

int main(void) {
    system_init();
    
    uint32_t last_update_time = 0;
    
    while (1) {
        uint32_t now = Millis();
        
       
        if ((now - last_update_time) >= 10) {
            switches_update();
            
            // Check for gear shifts
            if (switches_is_upshift_pressed()) {
                wheel_state.current_gear = gear_upshift();
                wheel_state.last_gear_change_time = now;
            }
            
            if (switches_is_downshift_pressed()) {
                wheel_state.current_gear = gear_downshift();
                wheel_state.last_gear_change_time = now;
            }
        }
        

        if ((now - last_update_time) >= UPDATE_INTERVAL_MS) {
            last_update_time = now;
     
            speed_sim_update();
            wheel_state.current_speed_kmh = speed_sim_get_speed_kmh();
            wheel_state.current_rpm = speed_sim_get_rpm();
            wheel_state.rpm_percentage = speed_sim_get_rpm_percentage();
            
           
            update_rpm_display(wheel_state.rpm_percentage);
            
          
            uint8_t gear_display = gear_get_display_value();
            update_7seg_display(gear_display, wheel_state.current_speed_kmh);
            

        }
    }
    
    return 0;
}