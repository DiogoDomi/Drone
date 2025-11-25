#ifndef TIME_MANAGER_H_
#define TIME_MANAGER_H_

#include <Arduino.h>

class TimeManager {
    private:

        uint32_t m_timestamp{};

    public:

        TimeManager() :
            m_timestamp{0}
            {}

        inline void begin() {
            configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
        }

        inline void update() {
            m_timestamp = time(nullptr);
        }

        inline uint32_t getTimestamp() const {
            return m_timestamp;
        }

};

#endif