#include <chrono>
#include <iostream>

class Time
{
public:
    Time()
    {
        std::chrono::duration<double> now_time_format = std::chrono::high_resolution_clock::now().time_since_epoch();
        time_epoch_to_initialisation = now_time_format.count();
    }

    float getCurrentTime()
    {
        std::chrono::duration<double> now_time_format = std::chrono::high_resolution_clock::now().time_since_epoch();
        const double time_now_since_epoch = now_time_format.count();

        float time_now_since_initialisation = time_now_since_epoch - time_epoch_to_initialisation;

        return time_now_since_initialisation;
    }

private:
    double time_epoch_to_initialisation;
};