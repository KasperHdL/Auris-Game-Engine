#pragma once

#include "Auris/Engine.hpp"

#include "Guide.hpp"
#include "Char.hpp"

#include <glm/gtc/random.hpp>

using namespace Auris;
class SpriteDemo : public Game{

    int spawnEntNum = 10;
    Guide* guide;
    vec2 position;
    float radius = 15;
    float scale = 3;
    vec3 ambientLight = vec3(0.1f);
    vec4 bgColor = vec4(0);

    void init(){
        camera = new Auris::Camera(1280, 720);

        Engine::instance->setAmbientLight(ambientLight);
        Engine::instance->setBackgroundColor(bgColor);


        guide = (Guide*) addEntity(make_shared<Guide>());


        for(int i = 0; i < spawnEntNum; i++){
            vec2 offset = glm::circularRand<float>(glm::linearRand<float>(0,radius));
            addEntity(make_shared<CharSprite>(position + offset,scale));

        }

    }

    void earlyUpdate(float dt){}
    void update(float dt){}
    void lateUpdate(float dt){}
    
    void shutdown(){}

    void imGui(){
        ImGui::Begin("SpriteDemo");
        ImGui::Text("Use the Arrow keys to move the Lights");

#ifdef DEBUG
        ImGui::Text("Press F2 for debug menu");
#else
        ImGui::Text("Running in Release Mode");
#endif
        ImGui::Text("DeltaTime: %f", Engine::instance->deltaTime * 1000);

        ImGui::Separator();
        ImGui::Text("Sprite DynamicPool");
        ImGui::Text("DynamicPool count    = %d", Engine::instance->renderSystem.spritePool.count);
        ImGui::Text("DynamicPool capacity = %d", Engine::instance->renderSystem.spritePool.capacity);


        ImGui::Separator();
        ImGui::Text("Spawning:");
        ImGui::DragFloat2("Position", &position.x);
        ImGui::DragFloat("Radius", &radius);
        ImGui::DragFloat("Scale", &scale);
        ImGui::DragInt("[X]", &spawnEntNum);

        if(ImGui::Button("Spawn [X] Entities Ani")){
            for(int i = 0; i < spawnEntNum; i++){
                vec2 offset = glm::circularRand<float>(glm::linearRand<float>(0,radius));
                addEntity(make_shared<CharAnim>(position + offset,scale));

            }
        }
        if(ImGui::Button("Spawn [X] Entities Sprite")){
            for(int i = 0; i < spawnEntNum; i++){
                vec2 offset = glm::circularRand<float>(glm::linearRand<float>(0,radius));
                addEntity(make_shared<CharSprite>(position + offset,scale));

            }
        }
        if(ImGui::Button("Spawn [X] Entities Unlit Sprite")){
            for(int i = 0; i < spawnEntNum; i++){
                vec2 offset = glm::circularRand<float>(glm::linearRand<float>(0,radius));
                addEntity(make_shared<CharUnlitSprite>(position + offset,scale));

            }
        }
        if(ImGui::Button("Delete all spawned Entities")){
            for(int i = 0; i < entities.size(); i++){
                if(entities[i]->type == "Character"){
                    destroyEntity(entities[i].get());
                }
            }
        }

#ifdef DEBUG
        ImGui::Separator();
        ImGui::DragFloat("Light Range", &guide->lightRange);
        if(ImGui::DragFloat("Light Offset", &guide->lightOffset)){
            guide->updateOffset();
        }
        for(int i = 0;i < 4; i++){
            ImGui::PushID(i);
            ImGui::ColorEdit3("Light Color", &guide->lights[i]->color.r);
            ImGui::PopID();
        }
        ImGui::Separator();
        if(ImGui::ColorEdit3("Ambient Color", &ambientLight.r)){
            Engine::instance->setAmbientLight(ambientLight);
        }
        if(ImGui::ColorEdit3("Background Color", &bgColor.r)){
            Engine::instance->setBackgroundColor(bgColor);
        }
#endif
        ImGui::End();
    }

};
