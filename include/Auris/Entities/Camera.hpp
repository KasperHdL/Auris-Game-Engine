#pragma once
#include "SRE/Camera.hpp"
#include "SRE/SimpleRenderEngine.hpp"

namespace Auris{

//! The camera class
    /*! To control the current camera of the game
    */
class Camera{
public:

    //! The camera constructor, taking 2-4 arguments
       /*!
        * Calculates the orthographic projection based on the arguments, and also centers the position of the camera.
        * \param right a float, that is the width of the camera.
        * \param top a float, that is the height of the camera.
        * \param near a float, that is the near clipping plane (default is -1).
        * \param far a float, that is the far clipping plane (default is 1).
       */
    Camera(float right, float top, float near=-1, float far=1);

    //! The camera destructor.
        /*! Deletes the Camera pointer.
        */
    ~Camera();
    //! A method to set the position, taking 1 argument.
        /*!
         * \param pos a vec2, that is the position to set the camera
        */
    void setPos(glm::vec2 pos);

    //! A method to get the position.
        /*!
         * \return a vec2, that is the position of the camera
        */
    glm::vec2 getPos();
    float getWidth();
    float getHeight();

    //! A method to set the rotation, taking 1 argument.
        /*! Calculates the rotation of the camera based on the argument inputted
         * \param z a float value, that is the rotation to set the camera
        */
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
