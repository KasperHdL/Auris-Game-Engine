#pragma once

#include "Auris/Engine.hpp"

#include "Guide.hpp"
#include "Char.hpp"

using namespace Auris;
class SpriteDemo : public Game{

    int spawnEntNum = 1000;

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

        ImGui::DragInt("Number of Entities to Spawn", &spawnEntNum);
        if(ImGui::Button("Spawn selected number")){


        }
        ImGui::End();
    }

    void spawnChar(){

    }
    
};
