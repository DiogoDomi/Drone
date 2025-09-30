#include "PIDManager.h"
#include "Arduino.h"

PIDManager::PIDManager(float kp, float ki, float kd)
    :
    m_kp(kp),
    m_ki(ki),
    m_kd(kd)
    {}

float PIDManager::compute(float realValue, float setpointValue, float deltaTime) {
    float error = setpointValue - realValue;

    float P = m_kp * error;

    m_accumulatedError += error * deltaTime;
    m_accumulatedError = constrain(m_accumulatedError, -200.0F, 200.0F);
    float I = m_ki * m_accumulatedError;

    float derivatedError = (error - m_previousError) / deltaTime;
    float D = m_kd * derivatedError;

    m_previousError = error;

    float PID = P + I + D;

    return PID;
}

void PIDManager::reset() {
    m_accumulatedError = 0.0F;
    m_previousError = 0.0F;
}