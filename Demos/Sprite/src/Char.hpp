#pragma once


#include "Auris/Entity.hpp"
#include "Auris/Utilities/AssetManager.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include <memory>

using namespace Auris;
class CharSprite : public Entity{
public: Sprite* sprite;

    CharSprite(vec2 position, bool withTexture = true):Entity(){
        name = "Sprite";
        type = "Character";

        sprite = RenderSystem::getSprite(this, AssetManager::getTexture("cartman.png"));
        transform->setPosition(position);

    }

    ~CharSprite(){
        RenderSystem::deleteSprite(sprite);
    }


};

class CharAnim : public Entity{
public:
    Sprite* sprite;
    SpriteSheet* sheet;
    shared_ptr<Animation> anim;

    CharAnim(vec2 position, bool withNormalMap = true):Entity(){
        name = "Sprite Animation";


        sheet = AssetManager::getSpriteSheet("player.json");

        anim = RenderSystem::getAnim(this, 1.0f);
        anim->makeSequence(sheet, "lower_run");

        sprite = RenderSystem::getSprite(this);
        sheet->setSpriteTo(sprite, "lower_run_3");


        transform->setPosition(position);
    }

    void update(float dt){
        anim->run(sprite, dt);
    }

    ~CharAnim(){
        RenderSystem::deleteAnim(anim);
        RenderSystem::deleteSprite(sprite);
        sheet = nullptr;

    }

};

