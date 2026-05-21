#ifndef WS2812_H
#define WS2812_H

#include <stdint.h>

#define WS2812_PIN_PORT PORTD
#define WS2812_PIN_DDR  DDRD
#define WS2812_PIN_BIT  6           // Pin 6 

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_Color_t;


void ws2812_init(void);


void ws2812_set_color(uint8_t index, RGB_Color_t color);

void ws2812_update(void);


void ws2812_clear(void);

void ws2812_set_brightness(uint8_t brightness);

#endif 