#ifndef PID_MANAGER_H_
#define PID_MANAGER_H_

class PIDManager {
    private:
        float m_kP{};
        float m_kI{};
        float m_kD{};

        float m_accumulatedError{};
        float m_lastFilteredRate{};

    public:
        PIDManager(float kP, float kI, float kD);

        float compute(float angle, float setpoint, float rate, float dt);

        inline void reset() {
            m_accumulatedError = 0.0F;
            m_lastFilteredRate = 0.0F;
        }
};

#endif