#pragma once
#include "Auris/Entities/Nugget.hpp"
#include "Auris/Constants.hpp"

#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Auris{
using namespace glm;

class Transform : public Nugget{
    public:
        vec3 position;
        vec2 scale;
        float rotation;

        Transform(Entity* entity):Nugget(entity){}

        mat4 getLocal();
        mat4 getGlobal();


};
}
