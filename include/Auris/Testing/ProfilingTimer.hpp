#pragma once
#include <SDL.h>

namespace Auris{

//! The Pofiling class
    /*! Used to control the timer of the profiling
    */
class ProfilingTimer{
private:
    Uint64 startStamp; /*!< A Uint64 value: startStamp. The start stamp of the timer. */
public:
    double length; /*!< A double value: length. The length of the timer. */

    //! A start method.
            /*!
             * Starts the timer, from the SDL_GetPerformanceCounter()
             * \sa SDL_GetPerformanceCounter()
            */
    void start(){
        startStamp = SDL_GetPerformanceCounter();
    }

    //! A stop method.
            /*!
             * Stops the timer
            */
    void stop(){
        length = SDL_GetPerformanceCounter() - startStamp;
        length /= (double)SDL_GetPerformanceFrequency();
    }

    //! A getStartTime method.
            /*!
             * Used to gather the start time of the timer
             * \return double. The start time of the timer
            */
    double getStartTime(){
        return (double)startStamp / SDL_GetPerformanceFrequency();
    }
};
}
