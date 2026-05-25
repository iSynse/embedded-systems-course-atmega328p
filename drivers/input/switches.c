#include "switches.h"
#include <avr/io.h>

#define DEBOUNCE_TIME_MS 20

static Switch_t switches[10] = {0};

static const uint8_t switch_pins[] = {
    PADDLE_UPSHIFT,
    PADDLE_DOWNSHIFT,
    BTN_12MM_1,
    BTN_12MM_2,
    BTN_7MM_1,
    BTN_7MM_2,
    BTN_7MM_3,
    BTN_7MM_4,
    BTN_7MM_5,
    BTN_7MM_6
};

#define NUM_SWITCHES (sizeof(switch_pins) / sizeof(switch_pins[0]))

void switches_init(void) {
   
    DDRD &= ~((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 7));
    PORTD |= ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 7));  // Pull-ups
    
    
    DDRB &= ~((1 << 0) | (1 << 1));
    PORTB |= ((1 << 0) | (1 << 1));  // Pull-ups
    
    
    DDRC &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4));
    PORTC |= ((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4));  // Pull-ups
    
    for (uint8_t i = 0; i < NUM_SWITCHES; i++) {
        switches[i].debounce_ms = DEBOUNCE_TIME_MS;
        switches[i].current_state = 0;
        switches[i].last_state = 0;
    }
}

static uint32_t millis_counter = 0;


void systick_increment(void) {
    millis_counter++;
}

uint32_t millis(void) {
    return millis_counter;
}

static bool read_pin(uint8_t pin) {
    if (pin < 8) {
        return !(PIND & (1 << pin));
    } else if (pin < 14) {
        return !(PINB & (1 << (pin - 8)));
    } else {
        return !(PINC & (1 << (pin - 14)));
    }
}

bool switches_update(void) {
    bool state_changed = false;
    uint32_t current_time = millis();
    
    for (uint8_t i = 0; i < NUM_SWITCHES; i++) {
        switches[i].current_state = read_pin(switch_pins[i]);
        

        if (switches[i].current_state != switches[i].last_state) {
            if ((current_time - switches[i].last_change_time) > switches[i].debounce_ms) {
                switches[i].last_state = switches[i].current_state;
                switches[i].last_change_time = current_time;
                switches[i].is_pressed = !switches[i].current_state;  // Invert for active-low
                state_changed = true;
            }
        } else {
            switches[i].is_pressed = false;  
        }
    }
    
    return state_changed;
}

bool switches_is_upshift_pressed(void) {
    return switches[0].is_pressed;
}

bool switches_is_downshift_pressed(void) {
    return switches[1].is_pressed;
}

bool switches_is_button_pressed(uint8_t button_index) {
    if (button_index < NUM_SWITCHES) {
        return switches[button_index].is_pressed;
    }
    return false;
}