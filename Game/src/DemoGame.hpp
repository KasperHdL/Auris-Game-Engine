#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Entities/Camera.hpp"

#include "Scenes/Scene1.hpp"
#include "Scenes/Scene2.hpp"
#include "Auris/Utilities/AudioPlayer.hpp"
#include <vector>

using namespace Auris;

class DemoGame : public Auris::Game {
    Scene1 scene1;

    vector<int> controllers;

//    int pistolShot;
//    int warSounds;

    int musicVolume = 128;
    int soundVolume = 128;

    void init() {
        camera = new Auris::Camera(1280, 720);
        loadScene(&scene1);
        Auris::Engine::world->SetGravity(b2Vec2(0, -9.8));
//        pistolShot = audioPlayer.addSound(Resource::getPath("pistolShot.wav").c_str(), 128);
//        warSounds = audioPlayer.addMusic(Resource::getPath("warSounds.wav").c_str(), 128);
//        audioPlayer.playMusic(warSounds);
    }

    void earlyUpdate(float dt){

    }

    void update(float dt){
//        if (Input::keyDown(SDL_SCANCODE_RETURN))
//            audioPlayer.playSound(pistolShot);

          //cout << id1 << ": " << Input::getControllerAxisState(id1,SDL_CONTROLLER_AXIS_TRIGGERRIGHT) << endl;
          //cout << id1 << ": " << Input::getControllerButtonState(id1,SDL_CONTROLLER_BUTTON_A) << endl;

          //cout << id2 << ": " << Input::getControllerAxisState(id2,SDL_CONTROLLER_AXIS_TRIGGERRIGHT) << endl;
          //cout << id2 << ": " << Input::getControllerButtonState(id2,SDL_CONTROLLER_BUTTON_A) << endl;

          //cout << id3 << ": " << Input::getControllerAxisState(id3,SDL_CONTROLLER_AXIS_TRIGGERRIGHT) << endl;
          //cout << id3 << ": " << Input::getControllerButtonState(id3,SDL_CONTROLLER_BUTTON_A) << endl;

    }

    void lateUpdate(float dt){

    }

    void shutdown(){

    }

    void controllerActivated(int controllerID){

    }

    void controllerConnected(){

    }

    void controllerDisconnected(int controllerID){

    }

    void imGUI(){

        bool open = true;

        ImGui::SetNextWindowPos(ImVec2(100,000));
        ImGui::Begin("#TestLabel",&open,ImVec2(500,100),0,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoInputs);
        ImGui::Text("Hello, world!");
        ImGui::End();

        // Show Button (with invisible window)
        // Note window may disappear behind other windows
        ImGui::SetNextWindowPos(ImVec2(200,100));
        ImGui::Begin("#Button",&open,ImVec2(100,25),0,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar);
        if (ImGui::Button("Click me")){
            std::cout << "Clicked"<<std::endl;
            }
        ImGui::End();
    }
};
