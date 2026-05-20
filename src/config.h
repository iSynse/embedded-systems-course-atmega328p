#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H


#define SPI_MOSI          11    
#define SPI_MISO          12   
#define SPI_SCK           13    
#define MAX7219_CS        10   


#define WS2812_PIN        6    
#define WS2812_COUNT      16    


// Paddle Shifter Switches (Upshift / Downshift)
#define PADDLE_UPSHIFT    0     // Micro switch for upshift 
#define PADDLE_DOWNSHIFT  1     // Micro switch for downshift


#define BTN_12MM_1        2     
#define BTN_12MM_2        3     

#define BTN_7MM_1         4
#define BTN_7MM_2         5
#define BTN_7MM_3         7
#define BTN_7MM_4         8
#define BTN_7MM_5         9
#define BTN_7MM_6         14    // A0 - analog pin used as digital
#define BTN_7MM_7         15    // A1
#define BTN_7MM_8         16    // A2


#define ENC1_CLK          17    // A3
#define ENC1_DT           18    // A4

// Encoder 2 (Brake Balance)
#define ENC2_CLK          19    // A5
#define ENC2_DT           20   

// Encoder 3 (Tire Temps)
#define ENC3_CLK          21
#define ENC3_DT           22

// Encoder 4 (Suspension)
#define ENC4_CLK          23
#define ENC4_DT           24

// Encoder 5 (DRS / Misc Control)
#define ENC5_CLK          25
#define ENC5_DT           26


#endif 