#pragma once

#include <chrono>

namespace Auris{
class Timer {
public:
    double elapsed;
    double duration;

    std::chrono::high_resolution_clock clock;

    std::chrono::time_point<clock> beginning;

    void reset() {
        elapsed = clock.now();
    }

    void start(float time) {

    }

    bool time() {
        if (elapsed > duration)
            return true;
    }
};
}
