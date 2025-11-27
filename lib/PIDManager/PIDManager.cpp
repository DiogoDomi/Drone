#include "PIDManager.h"
#include "Utils.h"

namespace { 
    constexpr float MAX_ACCUMULATED_ERROR = 200.0F;
    constexpr float LPF_ALPHA = 0.2F;
}

PIDManager::PIDManager(float kP, float kI, float kD)
    :
    m_kP(kP),
    m_kI(kI),
    m_kD(kD)
    {}

float PIDManager::compute(float angle, float setpoint, float rate, float dt) {
    float error = setpoint - angle;
    float P = m_kP * error;

    m_accumulatedError += error * dt;
    m_accumulatedError = Utils::mConstrain(m_accumulatedError, -MAX_ACCUMULATED_ERROR, MAX_ACCUMULATED_ERROR);
    float I = m_kI * m_accumulatedError;

    float D = 0.0F;

    if (dt > 0) {
        m_lastFilteredRate = m_lastFilteredRate + LPF_ALPHA * (rate - m_lastFilteredRate);
        D = -m_kD * m_lastFilteredRate;
    }

    return P + I + D;
}