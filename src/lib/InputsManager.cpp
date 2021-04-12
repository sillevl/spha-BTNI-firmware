#include "InputsManager.h"


InputsManager::InputsManager(I2C* i2c, PinName interruptPin) : interrupt(interruptPin), tca9555(i2c) {
    interrupt.mode(PullUp);
    interrupt.fall(mbed::callback(this, &InputsManager::interruptHandler));
    watchThread.start(mbed::callback(this, &InputsManager::watchChanges));
    previousStates = getInputs();
}

uint16_t InputsManager::getInputs() {
    return ~(tca9555.read());
}

void InputsManager::onStateChange(mbed::Callback<void(uint8_t, KeyState, uint32_t)> callback) {
    stateChanged = callback;
}

void InputsManager::interruptHandler() {
    stateChangedEvent.set(BUTTON_CHANGE_FLAG);
}

void InputsManager::watchChanges() {
    while(true) {
        stateChangedEvent.wait_any(BUTTON_CHANGE_FLAG);
        uint16_t states = getInputs();

        for(int channel = 0; channel < 16; channel++) {
            bool currentState = states & (0x01 << channel);
            bool previousState = previousStates & (0x01 << channel);

            if(!(currentState == previousState)) {
                auto currentTime = Kernel::Clock::now(); //duration_cast<milliseconds>(timer.elapsed_time()).count();
                auto previousChangeTime = lastChangeTime[channel];
                uint32_t timeSinceChange = duration_cast<milliseconds>(currentTime - previousChangeTime).count();

                lastChangeTime[channel] = currentTime;
                KeyState state = (currentState == 1) ? PRESSED : RELEASED;
                stateChanged(channel, state, timeSinceChange);
            }
        }
        previousStates = states;
    }
}