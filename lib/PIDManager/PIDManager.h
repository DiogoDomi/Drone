#ifndef PID_MANAGER_H_
#define PID_MANAGER_H_

class PIDManager {
    private:
        const float m_kp{};
        const float m_ki{};
        const float m_kd{};

        float m_accumulatedError{};
        float m_previousError{};

    public:
        PIDManager(float kp, float ki, float kd);
        float compute(float realValue, float setpointValue, float deltaTime);
        void reset();
};

#endif