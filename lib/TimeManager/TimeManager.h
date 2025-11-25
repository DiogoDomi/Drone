#ifndef TIME_MANAGER_H_
#define TIME_MANAGER_H_

#include <cstdint>

class TimeManager {
    private:

        uint32_t m_timestamp{};

    public:

        TimeManager();

        void begin();
        void update();

        inline uint32_t getTimestamp() const {
            return m_timestamp;
        }

};

#endif