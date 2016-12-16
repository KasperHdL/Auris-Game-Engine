#pragma once

#include "Auris/Entity.hpp"
#include "Auris/Entities/Light.hpp"
#include "Auris/Entities/Camera.hpp"
#include "Auris/Action.hpp"
#include "SRE/Debug.hpp"
#include <memory>

using namespace Auris;
using namespace glm;
class Guide : public Entity{
    public:

    Auris::Light* lights[4];
    Auris::Camera* camera;

    float speed = 10;

    Guide():Entity(){
        name = "Lights";
        float lightOffset = 10;
        for(int i = 0;i < 4; i++){
            lights[i] = (Auris::Light*) Game::instance->addEntity(make_shared<Auris::Light>(glm::vec2((i % 2) * lightOffset - lightOffset / 2,(i / 2) * lightOffset - lightOffset/2))); 
            addChild(lights[i]);
        }

    }

    void update(float dt){
        glm::vec2 vel = vec2(0);
        if(Input::keyHeld(Action::w) || Input::keyHeld(SDL_SCANCODE_UP)){
            vel.y += speed * dt;
        }else if(Input::keyHeld(Action::s) || Input::keyHeld(SDL_SCANCODE_DOWN)){
            vel.y -= speed * dt;
        }
        if(Input::keyHeld(Action::a) || Input::keyHeld(SDL_SCANCODE_LEFT)){
            vel.x -= speed * dt;
        }else if(Input::keyHeld(Action::d) || Input::keyHeld(SDL_SCANCODE_RIGHT)){
            vel.x += speed * dt;
        }

        transform->position += vec3(vel,0);
        //camera->setPos(transform->position);

    }

    void inspectorImGui(){
        Entity::inspectorImGui();
        ImGui::Separator();
        ImGui::DragFloat("Speed", &speed);
    }

    void debugDraw(){
        vec3 p = transform->position * Constants::METERS_TO_PIXELS;
        SRE::Debug::setColor(vec4(1));
        SRE::Debug::drawLine(vec3(p - vec3(-5,0,0)), vec3(p + vec3(5,0,0)));
        SRE::Debug::drawLine(vec3(p - vec3(0,-5,0)), vec3(p + vec3(0,5,0)));

    }

};
