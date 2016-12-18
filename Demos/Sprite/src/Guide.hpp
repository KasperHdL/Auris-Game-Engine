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

    Auris::Sprite* sprites[4];
    Auris::Light* lights[4];

    float speed = 10;
    float lightOffset = 6;
    float lightRange = 15;

    Guide():Entity(){
        name = "Lights";
        transform->setScale(2);
        transform->setPosition(vec3(0,0,0));

        vec3 colors[4] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0}};

        for(int i = 0;i < 4; i++){
            sprites[i] = RenderSystem::getSprite(this);
            glm::vec2 offset = glm::vec2((((i % 2)*2)-1) * lightOffset, (((i / 2)*2)-1) * lightOffset);
            sprites[i]->offset = vec3(offset,0);
            sprites[i]->material.color = vec4(colors[i],1);
            lights[i] = (Auris::Light*) Game::instance->addEntity(make_shared<Auris::Light>(offset));
            lights[i]->color = colors[i];
            lights[i]->range = lightRange;
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

        transform->addToPosition(vel);
        for(int i = 0; i < 4;i++)
            sprites[i]->material.color = vec4(lights[i]->color,1);

    }

    void inspectorImGui(){
        Entity::inspectorImGui();
        ImGui::Separator();
        ImGui::DragFloat("Speed", &speed);
        if(ImGui::DragFloat("Light Range", &lightRange)){
            for(int i = 0;i < 4; i++){
                lights[i]->range = lightRange;
            }
        }
        if(ImGui::DragFloat("Light Offset", &lightOffset)){
            updateOffset();
        }
    }

    void updateOffset(){
        for(int i = 0;i < 4; i++){
            glm::vec2 offset = glm::vec2((((i % 2)*2)-1) * lightOffset, (((i / 2)*2)-1) * lightOffset);
            sprites[i]->offset = vec3(offset,0);
            lights[i]->transform->setPosition(offset);
        }
    }

    void debugDraw(){
        vec2 p = transform->getPosition() * Constants::METERS_TO_PIXELS;
        SRE::Debug::setColor(vec4(1));
        SRE::Debug::drawLine(vec3(p + vec2(-6,0),0), vec3(p + vec2(5,0),0));
        SRE::Debug::drawLine(vec3(p + vec2(0,-6),0), vec3(p + vec2(0,5),0));

    }

};
