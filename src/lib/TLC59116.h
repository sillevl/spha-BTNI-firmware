#pragma once

#include "mbed.h"

class TLC59116{
    public:
    
    TLC59116(I2C* i2c, int address);
    TLC59116(PinName sda, PinName scl, int address);
    
    void setBrightness(float brightness);
    void setChannel(int channel, float brightness);
    void enable();
    void disable();
    
    protected:
    int address;
    I2C* i2c;
    
    void initialize();
    
    void setOutputState(int ledout0, int ledout1, int ledout2, int ledout3);
    
    private:
    void setRegister(int reg, int value);
    void setRegisters(int reg, char* value, int length, int mode = AUTO_INCREMENT_ALL_REGISTERS);
    
    static const int AUTO_INCREMENT_ALL_REGISTERS = 0x80;
    static const int AUTO_INCREMENT_BRIGHTNESS = 0xA0;
    static const int AUTO_INCREMENT_CONTROL = 0xC0;
    static const int AUTO_INCREMENT_BRIGHTNESS_CONTROL = 0xE0;
    static const int NO_AUTO_INCREMENT = 0x00;
    
    static const int GRPPWM = 0x12;
    static const int LEDOUT0 = 0x014;
};