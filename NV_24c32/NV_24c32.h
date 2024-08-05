#ifndef NV_24C32_H
#define NV_24C32_H

#include <stdint.h>
#include <Wire.h>

void memory_init();
void write_nv(const uint8_t* conf_address, int address, int size);
void read_nv(uint8_t* conf_address, int address, int size);

uint16_t count_checksum(const uint8_t* conf_address, int size);
bool memory_is_vaid(const uint8_t* conf_address, int size);

#endif
