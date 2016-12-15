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
         * \param pos a vec2, that is the position to set the camera.
        */
    void setPos(glm::vec2 pos);

    //! A method to get the position.
        /*!
         * \return a vec2, that is the position of the camera.
         * \sa translate()
        */
    glm::vec2 getPos();
    float getWidth();
    float getHeight();

    //! A method to set the rotation, taking 1 argument.
        /*! Calculates the rotation of the camera based on the argument inputted.
         * \param z a float value, that is the rotation to set the camera.
         * \sa rotate()
        */
    void setRotation(float z);

    //! A method to translate the camera, taking 1 argument.
        /*! Moves the camera the amount of input.
         * \param amount a vec2 value, that is the amount to move the camera.
         * \sa setPos().
        */
    void translate(glm::vec2 amount);

    //! A method to rotate the camera, taking 1 argument.
        /*! Rotates the camera the amount of input.
         * \param amount a float value, that is the amount to rotate the camera.
         * \sa setRotation().
        */
    void rotate(float amount);

    //! A method to zoom the camera, taking 1 argument.
        /*! Zooms the camera the amount of input.
         * \param amount a float value, that is the amount to zoom the camera (can be both positive and negative).
        */
    void zoom(float amount);

private:

    SRE::Camera* cam; /*!< A Camera pointer: cam. A reference to the SimpleRenderEngine Camera */
    float left; /*!< A float value: left. Used to calculate the orthographic projection from */
    float bottom; /*!< A float value: bottom. Used to calculate the orthographic projection from */
    float right; /*!< A float value: right. Used to calculate the orthographic projection from */
    float top; /*!< A float value: top. Used to calculate the orthographic projection from */
    float near; /*!< A float value: near. Used to calculate the orthographic projection from */
    float far; /*!< A float value: far. Used to calculate the orthographic projection from */
    float z; /*!< A float value: z. Used to calculate the rotation from */

    glm::vec3 up; /*!< A vec3 value: up. That is the up vector used to rotate the camera about */
    glm::vec2 pos; /*!< A vec2 value: pos. That is the position of the camera */

    //! A method to update the camera.
        /*! Updates the camera via the lookAt function in SimpleRenderEngine.
         * Does this after every change that has happend.
        */
    void updateCam();

};
}
