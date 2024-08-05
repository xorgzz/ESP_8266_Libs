#ifndef WAVESHARE_LCD_1602_H
#define WAVESHARE_LCD_1602_H

#include <Wire.h>
#include <stdint.h>

#define LCD_ADDR 0x7c>>1
#define COMMAND  0x00

class Waveshare_LCD {
    public:
        Waveshare_LCD();
        void clear();
        void print(String text);
        void print(String text, int line);
        void print(String text, int line, int cell);
        bool set_cursor(int line, int cell);

    private:
        void command(uint8_t data_byte);

};

#endif
