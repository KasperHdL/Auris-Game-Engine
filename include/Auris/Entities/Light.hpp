#pragma once

#include "Auris/Entity.hpp"

#include "SRE/SimpleRenderEngine.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Constants.hpp"
#include "glm/glm.hpp"

namespace Auris{
using namespace glm;

class Light : public Entity{
    public:

        enum Type{
            Point,
            Directional,
        };

        int lightNum; //!< between 0-4 maximum of four lights
        vec3 direction;//!< only used on directional lights
        vec3 color;//!< color of the light
        float range; //!< range of the light, 0 means inifinite

        Light(int lightNum, vec2 position = vec2(0,0), Type type = Point, bool alwaysOn = false):Entity(){

            transform->position = vec3(position,0);

            this->type = type;
            this->lightNum = lightNum;

            direction = vec3(0);
            color = vec3(1);
            range = 0;
        }

        void Update(float dt){

            SimpleRenderEngine::instance->setLight(
                    lightNum,
                    SRE::Light(
                        (SRE::LightType)type,
                        {
                            transform->position.x * Auris::Constants::METERS_TO_PIXELS,
                            transform->position.y * Auris::Constants::METERS_TO_PIXELS,
                            0
                        },
                        direction,
                        color,
                        range
                    )
                );

        }

    private:
        Type type;
        SRE::SimpleRenderEngine* sre;
};
}
