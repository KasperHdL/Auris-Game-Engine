#pragma once 

#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/GameObjects/Components/Animation.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/GameObjects/Components/Material.hpp"
#include "Auris/GameObjects/Components/SpriteSheet.hpp"
#include "Auris/Utilities/Resource.hpp"
#include "Auris/Utilities/BodyStandard.hpp"
#include "Auris/Utilities/Convert.hpp"
#include "Auris/Constants.hpp"
#include "glm/glm.hpp"
#include "SRE/Texture.hpp"
#include "SRE/Mesh.hpp"
#include <SDL2/SDL.h>


class Test : public Auris::GameObject{
    public:

    Auris::Material* mat;
    glm::vec2 pos;
    Test(glm::vec2 position):GameObject(){
        name = "testobject";

        
        mat = new Auris::Material();
        mat->setColor(vec4(1));
        mat->setTexture(SRE::Texture::getWhiteTexture());
        mat->setMesh(SRE::Mesh::createSphere());
        
        sprite = Auris::RenderSystem::getSprite(this, mat);
        sprite->scale = vec2(5,5);

        b2PolygonShape shape;
        shape.SetAsBox(1,1);

        body = Auris::Utilities::BodyStandard::getStaticBody(&shape, position, 30.0f);


    }

    void Update(float dt){
        SimpleRenderEngine::instance->setLight(1, Light(LightType::Point,{pos.x * Auris::Constants::METERS_TO_PIXELS,pos.y * Auris::Constants::METERS_TO_PIXELS,0},{0,0,0},{1,1,1},0));

        if (Auris::Input::keyHeld(SDL_SCANCODE_W)) {
            pos.y += 100 * dt;
        }else if (Auris::Input::keyHeld(SDL_SCANCODE_S)) {
            pos.y -= 100 * dt;
        }else if (Auris::Input::keyHeld(SDL_SCANCODE_A)) {
            pos.x -= 100 * dt;
        }else if (Auris::Input::keyHeld(SDL_SCANCODE_D)) {
            pos.x += 100 * dt;
        }

        setTransform(pos,0);
    }

    ~Test(){
        delete mat;
    }

};
