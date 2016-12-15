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

        //! An enum of Light::Type.
        /*! That holds information about the type of light.
         * Point and directional
         */
        enum Type{
            Point,
            Directional,
        };

        int lightNum; /*!< An int value: lightNum. That is the number of the specific light (between 0-3). */
        vec3 direction;/*!< A vec3 value: direction. That is the direction of the light (only used on directional lights) */
        vec3 color;/*!< A vec3 value: color. That is the color of the light */
        float range; /*!< A float value: range, that is the range of the light (0 means inifinite). */

        //! The light contructor taking 1-3 arguments.
            /*! Initializes a light with the input arguments.
             * \param lightNum an integer, that is the index of the light.
             * \param position a vec2, that is the position of the light (default vec2(0,0)).
             * \param type a Light::Type, that is the type of light (default Point).
            */
        Light(int lightNum, vec2 position = vec2(0,0), Type type = Point):Entity(){
            name = "Light";

            transform->position = vec3(position,0);

            this->type = type;
            this->lightNum = lightNum;

            direction = vec3(0);
            color = vec3(1);
            range = 0;
        }

        //! An update method taking 1 argument.
            /*! Updates the light every frame, to be able to move the light.
             * \param dt a float, that is the delta time.
            */
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
        Type type; /*!< A Light::Type value: type. A value to hold the type of light */
        SRE::SimpleRenderEngine* sre; /*!< A SimpleRenderEngine pointer: sre. A reference to the SimpleRenderEngine */
};
}
