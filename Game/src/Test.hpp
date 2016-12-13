#pragma once 

#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Entities/Nuggets/Animation.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Entities/Nuggets/Material.hpp"
#include "Auris/Entities/Nuggets/SpriteSheet.hpp"
#include "Auris/Utilities/Resource.hpp"
#include "Auris/Utilities/BodyStandard.hpp"
#include "Auris/Utilities/Convert.hpp"
#include "Auris/Constants.hpp"
#include "glm/glm.hpp"
#include "SRE/Texture.hpp"
#include "SRE/Mesh.hpp"
#include <SDL.h>


class Test : public Auris::Entity{
    public:

    Sprite* sprite;

    Test(glm::vec2 position):Entity(){
        name = "testobject";
       
        sprite = Auris::RenderSystem::getSprite(this);
        sprite->scale = vec2(5,5);

    }

    void Update(float dt){
        SimpleRenderEngine::instance->setLight(1, Light(LightType::Point,{transform->position.x * Auris::Constants::METERS_TO_PIXELS,transform->position.y * Auris::Constants::METERS_TO_PIXELS,0},{0,0,0},{1,1,1},0));

        if (Auris::Input::keyHeld(SDL_SCANCODE_W)) {
            transform->position.y += 100 * dt;
		}else if (Auris::Input::keyHeld(SDL_SCANCODE_S)) {
            transform->position.y -= 100 * dt;
		}else if (Auris::Input::keyHeld(SDL_SCANCODE_A)) {
            transform->position.x -= 100 * dt;
		}else if (Auris::Input::keyHeld(SDL_SCANCODE_D)) {
            transform->position.x += 100 * dt;
        }

    }

    ~Test(){
        RenderSystem::deleteSprite(sprite);
    }

};
