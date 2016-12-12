#pragma once
#include "SRE/Camera.hpp"
#include "SRE/SimpleRenderEngine.hpp"

namespace Auris{
class Camera{
public:

    Camera(float right, float top, float near=-1, float far=1);
    ~Camera();
    void setPos(glm::vec2 poss);
    void setRotation(float z);

    void moveCamera(glm::vec2 amount);
    void rotateCamera(float amount);
    void zoomCamera(float amount);

private:

    SRE::Camera* cam;
    float left;
    float bottom;
    float right;
    float top;
    float near;
    float far;
    float z;

    glm::vec3 up;

    glm::vec2 pos;

    void updateCam();

    };
}
