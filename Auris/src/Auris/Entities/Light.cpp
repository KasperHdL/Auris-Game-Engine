#include "Auris/Entities/Light.hpp"

namespace Auris{
int Light::lightCount = 0;

Light::Light(vec2 position, Type lightType, int lightNum):Entity(){
    if(lightNum < 0 || lightNum > 3)
        this->lightNum = lightCount % 4;
    else
        this->lightNum = lightNum;

    name = "Light " + std::to_string(lightCount);
    type = "Light";

    lightCount = ++lightCount;

    transform->position = vec3(position,0);
    globalPosition = transform->getGlobalPosition();

    this->lightType = lightType;

    direction = vec3(0);
    color = vec3(1);
    range = 0;
}

}
