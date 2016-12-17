#pragma once

#include <vector>
#include "glm/glm.hpp"

namespace Auris{

//! An enum class of InterpolationType.
/*! That holds information about the type of interpolation.
 * Linear, Bezier, Hermite, CatmullRom and BSpline.
 */
enum class InterpolationType{
    Linear,
    Bezier,
    Hermite,
    CatmullRom,
    BSpline
};

using namespace glm;

//! The Interpolation class.
    /*! Controls and have information of all interpolation in the engine
    */
class Interpolation{
public:

    //! The Interpolation contructor, taking 1 argument.
        /*! Saves the points to interpolate between, and set the initial type to Linear.
         * \param points a vector of vec2 values. The points to interpolate between.
        */
    Interpolation(std::vector<vec2> *points) :points(points) {
        interpolationType = InterpolationType::Linear;
    }

    //! A setInterpolation method, taking 1 argument.
        /*! Set what interpolation mode should be used.
         * \param i an Interpolation::InterpolationType. The interpolation type to set.
         * \sa Interpolation::InterpolationType
        */
    void setInterpolation(InterpolationType i) { interpolationType = i; }

    //! A getInterpolation method.
        /*! Get what interpolation mode is used.
         * \return Interpolation::InterpolationType. The interpolation used.
         * \sa Interpolation::InterpolationType
        */
    InterpolationType getInterpolationType() { return interpolationType; }

    //! A interpolate method, taking 1 argument.
        /*! Interpolates, based on the Interpolation::InterpolationType
         * \param t a float value. The time.
         * \sa Interpolation::InterpolationType
        */
    glm::vec2 interpolate(float t) { 
        switch (interpolationType){ 
            case InterpolationType::Bezier:
                return cubicBezier(t);
            case InterpolationType::CatmullRom:
                return catmullRom(t);
            case InterpolationType::Hermite:
                return hermite(t);
            case InterpolationType::BSpline:
                return bspline(t);
            default:
                return linear(t);
                break;
        }
    }
    InterpolationType interpolationType; /*!< An Interpolation::InterpolationType value: interpolationType. The interpolation type. */
private:
    std::vector<vec2> *points; /*!< A vector of vec2 pointers: points. The points to interpolate between. */

    //! A linear method, taking 1 argument.
        /*! Linear interpolation
         * \param t a float value. The time.
         * \sa interpolate()
        */
    glm::vec2 linear(float t) {
        std::vector<vec2> &points = *(this->points);
        return (1-t)* points[0] +
               t * points[1];
    }

    //! A cubicBezier method, taking 1 argument.
        /*! Cubic Bezier interpolation
         * \param t a float value. The time.
         * \sa interpolate()
        */
    glm::vec2 cubicBezier(float t) {
        std::vector<vec2> &points = *(this->points);
        return (float)pow(1-t,3) * points[0] +
               3*(float)pow(1-t,2)*t * points[1] +
               3*(1-t)*t*t * points[2] +
               (float)pow(t,3) * points[3];
    }

    //! A hermite method, taking 1 argument.
        /*! Hermite interpolation
         * \param t a float value. The time.
         * \sa interpolate()
        */
    glm::vec2 hermite(float t) {
        std::vector<vec2> &points = *(this->points);
        float t2 = t*t;
        float t3 = t2*t;
        float a0 = 1-(3*t2)+(2*t3);
        float a1 = (3*t2)+(-2*t3);
        float b0 = t-(2*t2)+t3;
        float b1 = -t2+t3;
        float tangentWeight = 3;
        return a0 * points[0] +
                a1* points[1] +
                b0 * (points[2]-points[0])*tangentWeight +
                b1 * (points[3]-points[1])*tangentWeight;
    }

    //! A catmullRom method, taking 1 argument.
        /*! Catmull Rom interpolation
         * \param t a float value. The time.
         * \sa interpolate()
        */
    glm::vec2 catmullRom(float t) {
        std::vector<vec2> &points = *(this->points);
        float t2 = t*t;
        float t3 = t2*t;
        float a0 = -0.5f*t + t2 - 0.5f*t3;
        float a1 = 1 - 2.5f*t2 + 1.5f*t3;
        float a2 = 0.5f*t + 2*t2 -1.5f*t3;
        float a3 = -0.5f*t2 + 0.5f*t3;
        return a0 * points[0] +
               a1* points[1] +
               a2 * points[2] + 
               a3 * points[3];
    }

    //! A bspline method, taking 1 argument.
        /*! B spline interpolation
         * \param t a float value. The time.
         * \sa interpolate()
        */
    glm::vec2 bspline(float t) {
        std::vector<vec2> &points = *(this->points);
        float t2 = t*t;
        float t3 = t2*t;
        float a0 = 1 -3*t + 3*t2 - t3;
        float a1 = 4 - 6*t2 + 3*t3;
        float a2 = 1+3*t + 3*t2 -3*t3;
        float a3 = t3;
        return (a0 * points[0] +
               a1* points[1] +
               a2 * points[2] +
               a3 * points[3])*(1/6.0f);
    }
};
}
