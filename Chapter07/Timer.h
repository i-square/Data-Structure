#ifndef DS_CH07_TIMER_H
#define DS_CH07_TIMER_H

#include <chrono>
using namespace std::chrono;

class Timer {
public:
    using s = seconds;
    using ms = milliseconds;
    using us = microseconds;
    using ns = nanoseconds;

public:
    Timer() : tpStart(high_resolution_clock::now()), tpStop(tpStart) {}

public:
    void start() { tpStart = high_resolution_clock::now(); }
    void stop() { tpStop = high_resolution_clock::now(); }

    template <typename span>
    auto delta() const { return duration_cast<span>(tpStop - tpStart).count(); }

    template <typename span>
    auto stop_delta() { stop(); return duration_cast<span>(tpStop - tpStart).count(); }

    template <typename span>
    auto stop_delta_start()
    {
        stop();
        auto ts = duration_cast<span>(tpStop - tpStart).count();
        start();
        return ts;
    }

private:
    time_point<high_resolution_clock> tpStart;
    time_point<high_resolution_clock> tpStop;
};

#endif // DS_CH07_TIMER_H
