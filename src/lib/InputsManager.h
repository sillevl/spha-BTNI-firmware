#pragma once

#include "mbed.h"
#include "TCA9555.h"

using namespace std::chrono;

class InputsManager {

    public:
    enum KeyState {  RELEASED = 0, PRESSED = 1 };

    InputsManager(I2C* i2c, PinName interruptPin);
    void onStateChange(mbed::Callback<void(uint8_t, KeyState, uint32_t)> cb);

    uint16_t getInputs();

    private:
    InterruptIn interrupt;
    TCA9555 tca9555;
    mbed::Callback<void(uint8_t, KeyState, uint32_t)> stateChanged;
    EventFlags stateChangedEvent;
    Thread watchThread;
    uint16_t previousStates;
    std::chrono::time_point<rtos::Kernel::Clock> lastChangeTime[16];

    void interruptHandler();
    void watchChanges();

    static const int BUTTON_CHANGE_FLAG = 0x01;
};