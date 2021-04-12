#pragma once

#include "mbed.h"

class LedManager {

    public:
    LedManager();

    DigitalOut status;
    DigitalOut communication;

    private:
    static const PinName STATUS_LED_PIN = PB_0;
    static const PinName COMMUNICATION_LED_PIN = PB_1;
};