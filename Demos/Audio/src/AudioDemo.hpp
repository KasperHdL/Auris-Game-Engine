#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Utilities/AudioPlayer.hpp"
#include "Auris/Utilities/AssetManager.hpp"

#include "SRE/imgui_sre.hpp"

#include "glm/glm.hpp"

using namespace glm;
using namespace Auris;

class AudioDemo : public Game {

    void init() {

    }

    void earlyUpdate(float deltaTime) {

    }

    void update(float deltaTime) {

    }

    void lateUpdate() {

    }

    void drawDebugImGui(){
        ImGui::Begin("Showcases"); 
 
        ImGui::Text("Startup Properties");


        if(ImGui::Button("Startup")){

        }

        ImGui::Separator();
        //ImGui::DragFloat2("Global Acceleration", 0.1f);
        //ImGui::DragFloat2("TimeScale", &particleSystem.timeScale, 0.1f);
        ImGui::Separator();

        ImGui::Text("Update Properties");
        //ImGui::DragInt("Num Emit Particles");
        //ImGui::ColorEdit4("End Color");
        //ImGui::DragFloat("End Size", &endSize, 0.1f);
     
        ImGui::Separator();


    }

    void shutdown() {

    }

};
