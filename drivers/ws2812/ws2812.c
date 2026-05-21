#include "ws2812.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

static RGB_Color_t led_buffer[WS2812_COUNT];
static uint8_t brightness_level = 255;


static inline void ws2812_send_byte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
    
        if (byte & (1 << (7 - i))) {
   
            WS2812_PIN_PORT |= (1 << WS2812_PIN_BIT);   // Set high
            _delay_us(0.8);
            WS2812_PIN_PORT &= ~(1 << WS2812_PIN_BIT);  // Set low
            _delay_us(0.45);
        } else {
            
            WS2812_PIN_PORT |= (1 << WS2812_PIN_BIT);   // Set high
            _delay_us(0.4);
            WS2812_PIN_PORT &= ~(1 << WS2812_PIN_BIT);  // Set low
            _delay_us(0.85);
        }
    }
}

void ws2812_init(void) {
    // Set WS2812 pin as output
    WS2812_PIN_DDR |= (1 << WS2812_PIN_BIT);
    WS2812_PIN_PORT &= ~(1 << WS2812_PIN_BIT);  // Start low
    
    // Clear LED buffer
    for (uint8_t i = 0; i < WS2812_COUNT; i++) {
        led_buffer[i].r = 0;
        led_buffer[i].g = 0;
        led_buffer[i].b = 0;
    }
}

void ws2812_set_color(uint8_t index, RGB_Color_t color) {
    if (index < WS2812_COUNT) {
        // Apply brightness scaling
        led_buffer[index].r = (color.r * brightness_level) / 255;
        led_buffer[index].g = (color.g * brightness_level) / 255;
        led_buffer[index].b = (color.b * brightness_level) / 255;
    }
}

void ws2812_update(void) {
    cli();  
    
    
    for (uint8_t i = 0; i < WS2812_COUNT; i++) {
        // WS2812 expects GRB order 
        ws2812_send_byte(led_buffer[i].g);
        ws2812_send_byte(led_buffer[i].r);
        ws2812_send_byte(led_buffer[i].b);
    }
    
    sei();  
    
    
   _delay_us(50);
}

void ws2812_clear(void) {
    for (uint8_t i = 0; i < WS2812_COUNT; i++) {
        led_buffer[i].r = 0;
        led_buffer[i].g = 0;
        led_buffer[i].b = 0;
    }
    ws2812_update();
}

void ws2812_set_brightness(uint8_t brightness) {
    brightness_level = brightness;
}