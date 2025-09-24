#ifndef IMU_DATA_H_
#define IMU_DATA_H_

struct IMUData {
    float elapsedTime{};
    float pitch{};
    float roll{};
    float yaw{};
};

#endif