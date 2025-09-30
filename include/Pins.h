#ifndef PINS_H_
#define PINS_H_

#include <cstdint>

namespace Pins {
    namespace MPU {
        // MPU6050 I2C & INT
        constexpr uint8_t SCL_PIN = 0;          // D3
        constexpr uint8_t SDA_PIN = 2;          // D4
        constexpr uint8_t INTERRUPT_PIN = 4;    // D2
    }

    namespace GPS {
        // GPS RX/TX
        constexpr uint8_t RX_PIN = 5;           // D1
        constexpr int8_t TX_PIN = -1;           // Not used
    }

    namespace ESC {
        // ESCs PWM
        constexpr uint8_t MOTOR_FL_PIN = 14;    // D5   | -> Motor 1
        constexpr uint8_t MOTOR_FR_PIN = 12;    // D6  | -> Motor 2
        constexpr uint8_t MOTOR_BR_PIN = 13;    // D7  | -> Motor 3
        constexpr uint8_t MOTOR_BL_PIN = 15;    // D8  | -> Motor 4
    }
};

#endif