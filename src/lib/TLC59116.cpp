#include "TLC59116.h"

TLC59116::TLC59116(I2C* _i2c, int _address): address(_address)
{
    this->i2c = _i2c;
    initialize();
}

TLC59116::TLC59116(PinName sda, PinName scl, int _address): address(_address)
{
    this->i2c = new I2C(sda, scl);
    initialize();
}

void TLC59116::initialize()
{
    // oscillator set to normal mode 
    enable();
    // enable individual brightness and group dimming
    setOutputState(0xFF,0xFF,0xFF,0xFF);
}

void TLC59116::enable()
{
    // should readout register state first
    setRegister(0,0);
}

void TLC59116::disable()
{
    // should readout register state first
    setRegister(0,1 << 4);
}

void TLC59116::setOutputState(int ledout0, int ledout1, int ledout2, int ledout3)
{
    setRegister(0x14,ledout0);
    setRegister(0x15,ledout1);
    setRegister(0x16,ledout2);
    setRegister(0x17,ledout3);
}

void TLC59116::setChannel(int led, float brightness)
{
    char data[] = {NO_AUTO_INCREMENT + 0x02 + led, brightness * 255.0};
    i2c->write(address, data, 2);
}


void TLC59116::setBrightness(float brightness)
{
    setRegister(GRPPWM, brightness * 255.0);
}

void TLC59116::setRegister(int reg, int value)
{
    char data[] = {NO_AUTO_INCREMENT + reg, value};
    i2c->write(address, data, 2);
}

void TLC59116::setRegisters(int reg, char* value, int length, int mode)
{
    // not implemented yet
}
