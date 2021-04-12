#include "mbed.h"
#include "SixPack.h"
#include "lib/LedManager.h"
#include "lib/InputsManager.h"
#include "lib/TLC59116.h"

using namespace SixPackLib;

static const uint16_t FirmwareVersion = 0x0010;
static const uint16_t DeviceType = 0x0020;

static const PinName SDA_PIN = PB_7;
static const PinName SCL_PIN = PB_6;
static const PinName STATUS_LED = PB_0;
static const PinName CAN_TXD = PA_11;
static const PinName CAN_RXD = PA_12;
static const PinName SERIAL_RX_PIN = PA_3;
static const PinName SERIAL_TX_PIN = PA_2;
static const PinName IO_INTERRUPT_PIN = PB_5;


I2C i2c(SDA_PIN, SCL_PIN);
CAN can(CAN_TXD, CAN_RXD, 500000);

LedManager leds;
InputsManager inputs(&i2c, IO_INTERRUPT_PIN);

static const int I2C_ADDRESS = 0xC0;
TLC59116 frontpanel(&i2c,I2C_ADDRESS);

SixPack sixPack(&can);

int main() {
    printf("*** 16 Channel input interface ***\r\n");

    frontpanel.enable();
    
    sixPack.setStatusLed(STATUS_LED);
    sixPack.setDeviceType(DeviceType);
    sixPack.setFirmwareVersion(FirmwareVersion);
    
    inputs.onStateChange([] (uint8_t index, InputsManager::KeyState state, uint32_t time) {
        frontpanel.setChannel(index, state == InputsManager::KeyState::PRESSED ? 1.0 : 0.0);
        sixPack.buttonUpdate( { index, (SixPack::ButtonState) state, time } );
    });
}