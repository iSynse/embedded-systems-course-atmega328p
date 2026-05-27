#include "max7219.h"
#include <avr/io.h>
#include <util/delay.h>

// 7-segment patterns for digits 0-9, and letters R, N, P, and blank
// Index 0-9: digits, 10: blank, 11: R, 12: N, 13: P
static const uint8_t segment_patterns[] = {
    0x7E,  // 0: 01111110
    0x30,  // 1: 00110000
    0x6D,  // 2: 01101101
    0x79,  // 3: 01111001
    0x33,  // 4: 00110011
    0x5B,  // 5: 01011011
    0x5F,  // 6: 01011111
    0x70,  // 7: 01110000
    0x7F,  // 8: 01111111
    0x7B,  // 9: 01011011
    0x00,  // 10: blank/space
    0x05,  // 11: R (01010101)
    0x37,  // 12: N (00110111)
    0x73   // 13: P (01110011)
};


static void spi_init(void) {
  
    DDRB |= (1 << 5) | (1 << 3) | (1 << 2);  // SCK(PB5), MOSI(PB3), CS(PB2)
    

    SPCR = (1 << SPE) | (1 << MSTR) | (0 << SPR1) | (1 << SPR0);
}

static void spi_transmit_byte(uint8_t byte) {
    SPDR = byte;
    while (!(SPSR & (1 << SPIF)));  
}

void max7219_init(void) {
    spi_init();
    _delay_ms(100);  
    
    max7219_write_register(MAX7219_REG_SHUTDOWN, 1);
    max7219_write_register(MAX7219_REG_DECODE, 0x00);       // Disable BCD decode - use raw patterns
    max7219_write_register(MAX7219_REG_SCAN_LIMIT, 3);      // 4 digits
    max7219_write_register(MAX7219_REG_INTENSITY, 10);      // Brightness
    max7219_write_register(MAX7219_REG_DISP_TEST, 0);   
    
    // Clear all digits
    for (uint8_t i = 0; i < 4; i++) {
        max7219_write_register(MAX7219_REG_DIG0 + i, 0x00);  
    }
}

void max7219_write_register(uint8_t address, uint8_t data) {
  
    PORTB &= ~(1 << 2);
    _delay_us(10);
    
   
    spi_transmit_byte(address);
    
  
    spi_transmit_byte(data);
    
    
    PORTB |= (1 << 2);
    _delay_us(10);
}

void max7219_display_digit(uint8_t position, uint8_t digit) {
    if (position > 3) return; 
    
    uint8_t reg = MAX7219_REG_DIG0 + position;
    uint8_t pattern;
    
    if (digit > 13) {
        pattern = 0x00;  // Blank for invalid digits
    } else {
        pattern = segment_patterns[digit];
    }
    
    max7219_write_register(reg, pattern);
}

void max7219_display_gear_speed(uint8_t gear, uint16_t speed) {

    uint8_t speed_tens = (speed / 10) % 10;
    uint8_t speed_ones = speed % 10;
    

    max7219_display_digit(0, gear);
    

    if (speed >= 100) {
        max7219_display_digit(1, (speed / 100) % 10);
    } else {
        max7219_display_digit(1, 10);  // 10 = blank pattern
    }
    

    max7219_display_digit(2, speed_tens);
    

    max7219_display_digit(3, speed_ones);
}

void max7219_set_brightness(uint8_t brightness) {
    if (brightness > 15) brightness = 15;
    max7219_write_register(MAX7219_REG_INTENSITY, brightness);
}