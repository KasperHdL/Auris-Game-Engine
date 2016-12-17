#pragma once

#include "Auris/Engine.hpp"

#include "Guide.hpp"
#include "Char.hpp"

#include <glm/gtc/random.hpp>

using namespace Auris;
class SpriteDemo : public Game{

    int spawnEntNum = 1000;

    vec2 position;
    float radius;
    bool spawnAnim = false;
    bool spawnSprite = true;

    void init(){
        camera = new Auris::Camera(1280, 720);

        auto guide = (Guide*) addEntity(make_shared<Guide>());
        guide->camera = camera;
    }

    void earlyUpdate(float dt){}
    void update(float dt){}
    void lateUpdate(float dt){}
    
    void shutdown(){}

    void drawDebugImGui(){
        ImGui::Begin("SpriteDemo");
        ImGui::Text("Press F2 for debug menu");

        if(ImGui::Checkbox("Spawn Animation", &spawnAnim))
            spawnSprite = !spawnSprite;

        ImGui::SameLine();
        if(ImGui::Checkbox("Spawn Sprite", &spawnSprite))
            spawnAnim = !spawnAnim;

        ImGui::DragFloat2("Position", &position.x);
        ImGui::DragFloat("Radius", &radius);
        ImGui::Separator();
        ImGui::DragInt("Number of Entities to Spawn", &spawnEntNum);
        ImGui::Text("Pool cout is %d", Engine::instance->renderSystem.spritePool.count);
        ImGui::Text("Pool limit is %d", Engine::instance->renderSystem.spritePool.capacity);
        if(ImGui::Button("Spawn selected number")){
            for(int i = 0; i < spawnEntNum; i++){
                spawnChar();
            }

        }
        ImGui::End();
    }

    void spawnChar(){
        if(spawnSprite)
            addEntity(make_shared<CharSprite>(vec2(0)));
        if(spawnAnim)
            addEntity(make_shared<CharAnim>(vec2(0)));

    }
    
};
