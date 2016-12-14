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

        Transform(Entity* entity):Nugget(entity){
            position = vec3(0,0,0);
            scale = vec2(1,1);
            rotation = 0;
        
        }

        mat4 getLocal(vec3 offset = vec3(0));
        mat4 getGlobal(vec3 offset = vec3(0));


};
}
