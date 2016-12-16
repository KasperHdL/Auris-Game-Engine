#pragma once

#include "Auris/Entity.hpp"

#include "SRE/SimpleRenderEngine.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Constants.hpp"
#include "glm/glm.hpp"

namespace Auris{
using namespace glm;

//! The Light class that extend the Entity class
    /*! Used to control the lights. There can only be 4 rendered lights, if Light are constantly added only the four newest lights will be shown, unless you pass the lightNum argument which overrides the automatic numbering system.
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

        vec3 direction;/*!< A vec3 value: direction. That is the direction of the light (only used on directional lights) */
        vec3 color;/*!< A vec3 value: color. That is the color of the light */
        float range; /*!< A float value: range, that is the range of the light (0 means inifinite). */
        static int lightCount; /*!< An int value: lightCount. The total number of instances of Light*/


        //! The light contructor taking 1-3 arguments.
            /*! Initializes a light with the input arguments.
             * \param position a vec2, that is the position of the light (default vec2(0,0)).
             * \param type a Light::Type, that is the type of light (default Point).
             * \param lightNum an integer, overrides the automatic numbering, There can only be 4 rendered lights.
            */
        Light(vec2 position = vec2(0,0), Type lightType = Point, int lightNum = -1);

        //! An update method taking 1 argument.
            /*! Updates the light every frame, to be able to move the light.
             * \param dt a float, that is the delta time.
            */
        void update(float dt){
            SRE::SimpleRenderEngine::instance->setLight(
                lightNum,
                SRE::Light(
                (SRE::LightType)lightType,
                {
                    transform->position.x * Auris::Constants::METERS_TO_PIXELS,
                    transform->position.y * Auris::Constants::METERS_TO_PIXELS,
                    0
                },
                direction,
                color,
                range * Auris::Constants::METERS_TO_PIXELS
                ));

        }

        ////////////
        //DEBUG
        //

        float iconScale = 10;//!< A float value, that indicates the size in pixels of the icon, can be changed in the inspector

        void inspectorImGui(){
            Entity::inspectorImGui();
            ImGui::Separator();

            ImGui::Text("Light Number(channel) %d", lightNum);
            lightNum = glm::clamp<int>(lightNum, 0, 3);
            if(lightType == Type::Directional)
                ImGui::DragFloat3("Direction", &direction.x);
            ImGui::ColorEdit3("Light Color", &color.r);
            ImGui::DragFloat("Light Range", &range, 0.1f);
            ImGui::Separator();
            ImGui::DragFloat("Light Icon Scale", &iconScale, 0.1f);

        }


        void debugDraw(){
            float scale = iconScale;
            vec2 p = transform->position * Auris::Constants::METERS_TO_PIXELS;

            SRE::Debug::setColor(vec4(1,1,1,1));
            SRE::Debug::drawLine(vec3(p.x - scale, p.y,0), vec3(p.x + scale, p.y,0));
            SRE::Debug::drawLine(vec3(p.x, p.y - scale,0), vec3(p.x, p.y + scale,0));
            SRE::Debug::setColor(vec4(color,1));
            SRE::Debug::drawLine(vec3(p.x - scale, p.y - scale,0), vec3(p.x + scale, p.y + scale,0));
            SRE::Debug::drawLine(vec3(p.x - scale, p.y + scale,0), vec3(p.x + scale, p.y - scale,0));

        }




    private:
        int lightNum;/*!< An int value: lightNum. That is the number of the specific light (between 0-3). */
        Type lightType; /*!< A Light::Type value: type. A value to hold the type of light */

};
}
