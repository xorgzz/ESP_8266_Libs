#include "NV_24c32.h"

const int AT24C32_ADDRESS = 0x50;

void memory_init() {
    Wire.begin();
}

// Counts checksum from read memory
uint16_t count_checksum(const uint8_t* conf_address, int size) {
    int out = 0;
    for (int i=0; i<size; i++) {
        out += (uint8_t)conf_address[i];
    }
    return ~out;
}

// Writes data to NV memory
void write_nv(const uint8_t* conf_address, int address, int size) {
    Wire.beginTransmission(AT24C32_ADDRESS);
    Wire.write(address >> 8);
    Wire.write(address & 0xFF);

    for (int i=0; i<size; i++) {
        if(address%32 == 0 && i != 0) {
            Wire.endTransmission();
            delay(10);
            Wire.beginTransmission(AT24C32_ADDRESS);
            Wire.write(address >> 8);
            Wire.write(address & 0xFF);
        }

        Wire.write((uint8_t)conf_address[i]);
        address++;
    }
    Wire.endTransmission();
    delay(10);
}

// Reads data from NV memory
void read_nv(uint8_t* conf_address, int address, int size) {
    Wire.beginTransmission(AT24C32_ADDRESS);
    Wire.write(address >> 8);
    Wire.write(address & 0xFF);
    Wire.endTransmission();

    Wire.requestFrom((int)AT24C32_ADDRESS, (int)size);

    int i = 0;

    while(Wire.available()) {
        char c = (uint8_t)Wire.read();
        if (i > size) {
            break;
        }
        conf_address[i] = c;
        i++;
    }
}

// Compares main memory that was read to backup memory
bool memory_is_vaid(const uint8_t* conf_address, int size) {
    // read and comapre backup memory
    int address = 320;
    Wire.beginTransmission(AT24C32_ADDRESS);
    Wire.write(address >> 8);
    Wire.write(address & 0xFF);
    Wire.endTransmission();
    Wire.requestFrom((int)AT24C32_ADDRESS, (int)size);
    int i = 0;
    while(Wire.available()) {
        char c = (uint8_t)Wire.read();
        if (c != conf_address[i]) {
            return false;
        }
        i++;
    }
    return true;
}
