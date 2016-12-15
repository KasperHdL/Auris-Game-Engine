#include "Auris/Entities/Camera.hpp"
#include "glm/gtx/rotate_vector.hpp"

using namespace Auris;

Camera::Camera(float right, float top, float near, float far){
    this->left = -right/2;
    this->bottom = -top/2;
    this->right = right/2;
    this->top = top/2;
    this->near = near;
    this->far = far;
    this->pos.x = 0;
    this->pos.y = 0;
    this->z = 0;
    this->up = glm::vec3(0,1,0);
    cam = new SRE::Camera();
    cam->setOrthographicProjection(this->left,this->right,this->bottom,this->top,this->near,this->far);
    SRE::SimpleRenderEngine::instance->setCamera(cam);
    updateCam();
}

Camera::~Camera(){
    delete cam;
}

void Camera::updateCam(){
    cam->lookAt(glm::vec3(pos.x,pos.y,1),glm::vec3(pos.x,pos.y,-1),up);
}

void Camera::setPos(glm::vec2 pos){
    this->pos=pos;
    updateCam();
}

glm::vec2 Camera::getPos(){
    return pos;
}

float Camera::getWidth(){
    return right-left;
}

float Camera::getHeight(){
    return top-bottom;
}

void Camera::translate(glm::vec2 amount){
    pos += amount;
    updateCam();
}

void Camera::zoom(float amount){
    cam->setOrthographicProjection(left*amount,right*amount,bottom*amount,top*amount,near*amount,far*amount);
}

void Camera::setRotation(float z){
    this->z = z;
    up = glm::rotateZ(glm::vec3(0,1,0),this->z);
    updateCam();
}

void Camera::rotate(float amount){
    this->z += amount;
    up = glm::rotateZ(up,amount);
    updateCam();
}
