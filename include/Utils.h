#ifndef _UTILS_H_
#define _UTILS_H_

#include <Arduino.h>

namespace Utils {

    inline float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    inline int imap(int x, int in_min, int in_max, int out_min, int out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    inline float fConstrain(float x, float minVal, float maxVal) {
        if (x < minVal) return minVal;
        if (x > maxVal) return maxVal;
        return x;
    }

    inline int iConstrain(int x, int minVal, int maxVal) {
        if (x < minVal) return minVal;
        if (x > maxVal) return maxVal;
        return x;
    }
}

#endif;