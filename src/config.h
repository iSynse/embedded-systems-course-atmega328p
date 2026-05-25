#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H


#define SPI_MOSI          11    // PORTB.3
#define SPI_MISO          12    // PORTB.4
#define SPI_SCK           13    // PORTB.5
#define MAX7219_CS        10    // PORTB.2


#define WS2812_PIN        6     // PORTD.6
#define WS2812_COUNT      16    


// Paddle Shifter Switches (Upshift / Downshift) - PORTD
#define PADDLE_UPSHIFT    2     // Digital Pin 2 (PORTD.2)
#define PADDLE_DOWNSHIFT  3     // Digital Pin 3 (PORTD.3)

// 12MM Buttons - PORTD
#define BTN_12MM_1        4     // Digital Pin 4 (PORTD.4)
#define BTN_12MM_2        5     // Digital Pin 5 (PORTD.5)

// 7MM Buttons - PORTD, PORTB, PORTC
#define BTN_7MM_1         7     // Digital Pin 7 (PORTD.7)
#define BTN_7MM_2         8     // Digital Pin 8 (PORTB.0)
#define BTN_7MM_3         9     // Digital Pin 9 (PORTB.1)
#define BTN_7MM_4         14    // Analog Pin A0 (PORTC.0) 
#define BTN_7MM_5         15    // Analog Pin A1 (PORTC.1) 
#define BTN_7MM_6         16    // Analog Pin A2 (PORTC.2) 
#define BTN_7MM_7         17    // Analog Pin A3 (PORTC.3) 
#define BTN_7MM_8         18    // Analog Pin A4 (PORTC.4) 


#define ENC1_CLK          17    // A3
#define ENC1_DT           18    // A4


#define ENC2_CLK          19    // A5
#define ENC2_DT           20   


#define ENC3_CLK          21
#define ENC3_DT           22


#define ENC4_CLK          23
#define ENC4_DT           24


#define ENC5_CLK          25
#define ENC5_DT           26


#endif 