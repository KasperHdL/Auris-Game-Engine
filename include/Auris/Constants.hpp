#pragma once


namespace Auris{
//! A namespace for constants
namespace Constants{
    const float METERS_TO_PIXELS = 10.0f; /*!< Number of pixels per meter*/
    const float PIXELS_TO_METERS = 1.0f / METERS_TO_PIXELS; /*!< Meters per pixel*/
    const int VELOCITY_ITERATIONS = 16; /*!< A constant int value: VELOCITY_ITERATIONS. The velocity iterations of the physics world per frame */
    const int POSITION_ITERATIONS = 16; /*!< A constant int value: POSITION_ITERATIONS. The position iterations of the physics world per frame */
   static int width = 1280; /*!< An int value: width. The current width of the window */
   static int height = 720; /*!< An int value: height. The current height of the window */
}
}
