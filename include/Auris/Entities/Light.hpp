#pragma once

#include "Auris/Entity.hpp"

#include "SRE/SimpleRenderEngine.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Constants.hpp"
#include "glm/glm.hpp"

namespace Auris{
using namespace glm;

//! The Light class that extend the Entity class
    /*! Used to control the lights.
    */
class Light : public Entity{
    public:

        //! An enum of type.
        /*! That holds information about the type of light.
         * Point og directional
         */
        enum Type{
            Point,
            Directional,
        };

        int lightNum; //!< between 0-4 maximum of four lights
        vec3 direction;//!< only used on directional lights
        vec3 color;//!< color of the light
        float range; //!< range of the light, 0 means inifinite

        Light(int lightNum, vec2 position = vec2(0,0), Type type = Point, bool alwaysOn = false):Entity(){
            name = "Light";

            transform->position = vec3(position,0);

            this->type = type;
            this->lightNum = lightNum;

            direction = vec3(0);
            color = vec3(1);
            range = 0;
        }

        void update(float dt){

            SRE::SimpleRenderEngine::instance->setLight(
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

        virtual void inspectorImGui(){
            Entity::inspectorImGui();
            ImGui::Separator();

            ImGui::Text("Light Number(channel) %d", lightNum);
            lightNum = glm::clamp<int>(lightNum, 0, 3);
            if(type == Type::Directional)
                ImGui::DragFloat3("Direction", &direction.x);
            ImGui::ColorEdit3("Light Color", &color.r);
            ImGui::DragFloat("Light Range", &range, 0.1f);




        }

    private:
        Type type;
        SRE::SimpleRenderEngine* sre;
};
}
