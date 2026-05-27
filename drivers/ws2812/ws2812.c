#include "ws2812.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "config.h"

static RGB_Color_t led_buffer[WS2812_COUNT];
static uint8_t brightness_level = 255;


static inline void ws2812_send_byte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++) {
        if (byte & (1 << (7 - i))) {
            // Send "1": T1H=0.8µs, T1L=0.45µs (use 1µs for reliability)
            WS2812_PIN_PORT |= (1 << WS2812_PIN_BIT);   // Set high
            _delay_us(1);
            WS2812_PIN_PORT &= ~(1 << WS2812_PIN_BIT);  // Set low
            _delay_us(1);
        } else {
            // Send "0": T0H=0.4µs, T0L=0.85µs (use conservative timing)
            WS2812_PIN_PORT |= (1 << WS2812_PIN_BIT);   // Set high
            // Very short delay for HIGH - use inline NOPs for ~0.2µs
            asm volatile("nop\n nop\n");
            WS2812_PIN_PORT &= ~(1 << WS2812_PIN_BIT);  // Set low
            _delay_us(1);  // Wait for LOW phase
        }
    }
}

void ws2812_init(void) {
    // Set WS2812 pin as output
    WS2812_PIN_DDR |= (1 << WS2812_PIN_BIT);
    WS2812_PIN_PORT &= ~(1 << WS2812_PIN_BIT);  // Start low
    
    _delay_ms(1);  // Wait for LED strip to be ready
    
    // Clear LED buffer
    for (uint8_t i = 0; i < WS2812_COUNT; i++) {
        led_buffer[i].r = 0;
        led_buffer[i].g = 0;
        led_buffer[i].b = 0;
    }
    
    // Send initial clear command to ensure LEDs are off
    ws2812_update();
    _delay_ms(1);  // Wait for update to complete
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