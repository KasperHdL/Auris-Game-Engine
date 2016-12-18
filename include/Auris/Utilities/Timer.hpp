#pragma once

#include <chrono>

namespace Auris{

//! The Timer class
    /*! Used to make a timer, if you need it
    */
class Timer {
private:

    float currentTime; /*!< A float value: currentTime. The current time of the timer. */
    float endTime; /*!< A float value: endTime. The end time of the timer. */

public:

    //! A reset method.
        /*!
         * Reset the current timer back to 0.
        */
    void reset(){
        currentTime = 0;
    }

    //! A start method, taking 1 argument.
        /*!
         * Start the timer, with the value inputted
         * \param time a float value. The time, the timer should go to.
        */
    void start(float time) {
       endTime = time;
       currentTime = 0;
    }

    //! A time method.
        /*!
         * Alerts if the timer has passed!
         * \return bool. If the timer has passed or not.
        */
    bool time() {
        if (currentTime > endTime){
            return true;
        }else{
            return false;
        }
    }

    //! An update method, taking 1 argument.
        /*! Updates the timer
         * \param dt a float value. The delta time in seconds.
        */
    void update(float dt){
        currentTime += dt;
    }

    //! A getCurrentTime method.
        /*! A method to get the current time in the timer.
         * \return int. The current time.
        */
    int getCurrentTime(){
        return (int)currentTime;
    }
};
}
