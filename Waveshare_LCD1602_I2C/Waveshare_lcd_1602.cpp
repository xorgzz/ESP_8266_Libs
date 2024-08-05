#include "Waveshare_lcd_1602.h"

// Public
Waveshare_LCD::Waveshare_LCD() {
    Wire.begin();
    this->clear();
    this->command(0x0c);  // Turn on display
    this->command(0x28);  // Set 2-line display
}

void Waveshare_LCD::clear() {
    this->command(0x01); // Clear display & go to home (position line0:cell0)
}

void Waveshare_LCD::print(String text) {
    Wire.beginTransmission(LCD_ADDR);
    Wire.write(0x40); // Co = 0 & RS = 1 // Initiate data write
    for (int i=0; i<text.length(); i++) {
        Wire.write((uint8_t)text[i]);
    }
    Wire.endTransmission();
    delay(50);
}

void Waveshare_LCD::print(String text, int line) {
    // don't print if line out of bounds
    if (!this->set_cursor(line, 0)) return;

    Wire.beginTransmission(LCD_ADDR);
    Wire.write(0x40); // Co = 0 & RS = 1 // Initiate data write
    for (int i=0; i<text.length(); i++) {
        Wire.write((uint8_t)text[i]);
    }
    Wire.endTransmission();
    delay(50);
}

void Waveshare_LCD::print(String text, int line, int cell) {
    // don't print if line or cell out of bounds
    if (!this->set_cursor(line, cell)) return;

    Wire.beginTransmission(LCD_ADDR);
    Wire.write(0x40); // Co = 0 & RS = 1 // Initiate data write
    for (int i=0; i<text.length(); i++) {
        Wire.write((uint8_t)text[i]);
    }
    Wire.endTransmission();
    delay(50);
}

// line 0 || 1; cell 0->63;
bool Waveshare_LCD::set_cursor(int line, int cell) {
    // returns true if succeeds to set cursor
    // check if line & cell not out of bounds
    if (line > 1 || line < 0 || cell > 63 || cell < 0) {
        return false;
    }

    int address = cell;
    if (line == 1) address += 64;

    this->command(0x80+address);
    return true;
}

// Private
void Waveshare_LCD::command(uint8_t data_byte) {
    Wire.beginTransmission(LCD_ADDR);
    Wire.write(COMMAND); // Co = 0 & RS = 0
    Wire.write(data_byte);
    Wire.endTransmission();
    delay(50);
}
