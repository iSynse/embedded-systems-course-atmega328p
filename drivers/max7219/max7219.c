#include "max7219.h"
#include <avr/io.h>
#include <util/delay.h>


static void spi_init(void) {
  
    DDRB |= (1 << 2) | (1 << 1) | (1 << 3);  
    

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
    max7219_write_register(MAX7219_REG_DECODE, 0xFF);      
    max7219_write_register(MAX7219_REG_SCAN_LIMIT, 3);     
    max7219_write_register(MAX7219_REG_INTENSITY, 8);     
    max7219_write_register(MAX7219_REG_DISP_TEST, 0);   
    
   
    for (uint8_t i = 0; i < 4; i++) {
        max7219_write_register(MAX7219_REG_DIG0 + i, 0x0F);  
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
    
  
    uint8_t reg = MAX7219_REG_DIG0 + position + 1;
    
    if (digit > 9) {
        digit = 0x0F;  
    }
    
    max7219_write_register(reg, digit);
}

void max7219_display_gear_speed(uint8_t gear, uint16_t speed) {

    uint8_t speed_tens = (speed / 10) % 10;
    uint8_t speed_ones = speed % 10;
    

    max7219_display_digit(0, gear);
    

    if (speed >= 100) {
        max7219_display_digit(1, (speed / 100) % 10);
    } else {
        max7219_display_digit(1, 0x0F);  
    }
    
  
    max7219_display_digit(2, speed_tens);
    
  
    max7219_display_digit(3, speed_ones);
}

void max7219_set_brightness(uint8_t brightness) {
    if (brightness > 15) brightness = 15;
    max7219_write_register(MAX7219_REG_INTENSITY, brightness);
}