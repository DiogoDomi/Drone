#ifndef JOYSTICK_DATA_H_
#define JOYSTICK_DATA_H_

#include <cstdint>

struct JoystickData {
    int8_t lx{}, ly{}, rx{}, ry{};
};

#endif