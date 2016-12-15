#pragma once
#include <SDL.h>

namespace Auris{
class ProfilingTimer{
private:
    Uint64 startStamp;
public:
    double length;

    void start(){
        startStamp = SDL_GetPerformanceCounter();
    }

    void stop(){
        length = SDL_GetPerformanceCounter() - startStamp;
        length /= (double)SDL_GetPerformanceFrequency();
    }

    double getStartTime(){
        return (double)startStamp / SDL_GetPerformanceFrequency();
    }
};
}
