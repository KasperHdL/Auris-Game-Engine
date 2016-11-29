#pragma once

#include <vector>
#include "glm/glm.hpp"

namespace Auris{
enum class InterpolationType{
    Linear,
    Bezier,
    Hermite,
    CatmullRom,
    BSpline
};

using namespace glm;
class Interpolation{
public:

    Interpolation(std::vector<vec2> *points) :points(points) {
        interpolationType = InterpolationType::Linear;
    }

    void setInterpolation(InterpolationType i) { interpolationType = i; }
    InterpolationType getInterpolationType() { return interpolationType; }


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
    InterpolationType interpolationType;
private:
    std::vector<vec2> *points;

    glm::vec2 linear(float t) {
        std::vector<vec2> &points = *(this->points);
        return (1-t)* points[0] +
               t * points[1];
    }
    glm::vec2 cubicBezier(float t) {
        std::vector<vec2> &points = *(this->points);
        return (float)pow(1-t,3) * points[0] +
               3*(float)pow(1-t,2)*t * points[1] +
               3*(1-t)*t*t * points[2] +
               (float)pow(t,3) * points[3];
    }

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
