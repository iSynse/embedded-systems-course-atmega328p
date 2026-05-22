#ifndef MAX7219_H
#define MAX7219_H

#include <stdint.h>


#define MAX7219_REG_NOOP        0x00
#define MAX7219_REG_DIG0        0x01
#define MAX7219_REG_DIG1        0x02
#define MAX7219_REG_DIG2        0x03
#define MAX7219_REG_DIG3        0x04
#define MAX7219_REG_DIG4        0x05
#define MAX7219_REG_DIG5        0x06
#define MAX7219_REG_DIG6        0x07
#define MAX7219_REG_DIG7        0x08
#define MAX7219_REG_DECODE      0x09    // Decode mode (BCD)
#define MAX7219_REG_INTENSITY   0x0A    // LED intensity
#define MAX7219_REG_SCAN_LIMIT  0x0B    
#define MAX7219_REG_SHUTDOWN    0x0C    
#define MAX7219_REG_DISP_TEST   0x0F    // Display test


void max7219_init(void);


void max7219_write_register(uint8_t address, uint8_t data);


void max7219_display_digit(uint8_t position, uint8_t digit);


void max7219_display_number(uint16_t number);


void max7219_display_gear_speed(uint8_t gear, uint16_t speed);


void max7219_set_brightness(uint8_t brightness);

#endif