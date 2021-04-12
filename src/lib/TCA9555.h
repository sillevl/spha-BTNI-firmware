#pragma once

#include "mbed.h"

class TCA9555 {
    public:
    TCA9555(I2C* i2c);

    uint16_t read();

    private:
    I2C* i2c;

    uint8_t i2c_read_uint8(char address);

    static const char I2C_ADDRESS = 0x20 << 1;
    static const char CMD_INPUT_PORT_0 = 0x00;
    static const char CMD_INPUT_PORT_1 = 0x01;
};
