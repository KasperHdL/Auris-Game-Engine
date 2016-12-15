#pragma once
#include "SRE/Camera.hpp"
#include "SRE/SimpleRenderEngine.hpp"

namespace Auris{
class Camera {
public:

    //! The camera constructor which take in float to calculate the projection
       /*!
         \param right a float argument which is the width of the camera
         \param top a float argument which is the height of the camera
         \param near a float for the near clipping plane, its default is -1
         \param far a float for the far clipping plane, its default is 1
         \return void
       */
    Camera(float right, float top, float near=-1, float far=1);
    ~Camera();
    void setPos(glm::vec2 pos);
    glm::vec2 getPos();
    float getWidth();
    float getHeight();
    void setRotation(float z);

    void translate(glm::vec2 amount);
    void rotate(float amount);
    void zoom(float amount);

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
