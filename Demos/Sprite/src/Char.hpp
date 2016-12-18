#pragma once


#include "Auris/Entity.hpp"
#include "Auris/Utilities/AssetManager.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include <memory>

using namespace Auris;
class CharUnlitSprite : public Entity{
public:
    Sprite* sprite;

    CharUnlitSprite(vec2 position, float scale):Entity(){
        name = "Ent Unlit Sprite";
        type = "Character";

        sprite = RenderSystem::getSprite(this, AssetManager::getTexture("cartman.png"));
        transform->setPosition(vec3(position,0));
        transform->setScale(scale);

    }

    ~CharUnlitSprite(){
        RenderSystem::deleteSprite(sprite);
    }

    void inspectorImGui(){
        Entity::inspectorImGui();
        ImGui::Separator();
        if(ImGui::Button("Destroy")){
            Game::instance->destroyEntity(this);
        }
    }

};

class CharSprite : public Entity{
public:
    Sprite* sprite;

    CharSprite(vec2 position, float scale):Entity(){
        name = "Ent Lit Sprite";
        type = "Character";

        SpriteSheet* sheet = AssetManager::getSpriteSheet("player.json");
        sprite = RenderSystem::getSprite(this);
        sheet->setSpriteTo(sprite, "upper_3");

        transform->setPosition(vec3(position,0));
        transform->setScale(scale);

    }

    ~CharSprite(){
        RenderSystem::deleteSprite(sprite);
    }

    void inspectorImGui(){
        Entity::inspectorImGui();
        ImGui::Separator();
        if(ImGui::Button("Destroy")){
            Game::instance->destroyEntity(this);
        }
    }

};

class CharAnim : public Entity{
public:
    Sprite* sprite;
    SpriteSheet* sheet;
    shared_ptr<Animation> anim;

    CharAnim(vec2 position, float scale):Entity(){
        name = "Ent Animation";
        type = "Character";

        sheet = AssetManager::getSpriteSheet("player.json");

        anim = RenderSystem::getAnim(this, 1.0f);
        anim->makeSequence(sheet, "lower_run");

        sprite = RenderSystem::getSprite(this);
        sheet->setSpriteTo(sprite, "lower_run_3");


        transform->setPosition(vec3(position,0));
        transform->setScale(scale);
    }

    void update(float dt){
        anim->run(sprite, dt);
    }

    ~CharAnim(){
        RenderSystem::deleteAnim(anim);
        RenderSystem::deleteSprite(sprite);
        sheet = nullptr;

    }

    void inspectorImGui(){
        Entity::inspectorImGui();
        ImGui::Separator();
        if(ImGui::Button("Destroy")){
            Game::instance->destroyEntity(this);
        }
    }

};

