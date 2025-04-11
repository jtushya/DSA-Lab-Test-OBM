#include <chrono>

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoint;
    double getTimeDifference();

public:
    Timer();
    void start();
    void stop();
    double getDurationInSeconds();
    double getDurationInMilliSeconds();
    double getDurationInMicroSeconds();
};

Timer::Timer() {}

void Timer::start()
{
    startTimePoint = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
    endTimePoint = std::chrono::high_resolution_clock::now();
}

double Timer::getTimeDifference()
{
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();
    return end - start;
}

double Timer::getDurationInSeconds()
{
    return getDurationInMilliSeconds() * 0.001; // in seconds
}

double Timer::getDurationInMilliSeconds()
{
    return getTimeDifference() * 0.001; // in milli seconds
}

double Timer::getDurationInMicroSeconds()
{
    return getTimeDifference(); // in micro-seconds
}