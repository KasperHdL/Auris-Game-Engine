#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Entities/Camera.hpp"

#include "Scenes/Scene1.hpp"
#include "Scenes/Scene2.hpp"
#include "Auris/Utilities/AudioPlayer.hpp"
#include "Crosshair.hpp"
#include <vector>

using namespace Auris;

class DemoGame : public Auris::Game {
    Scene1 scene1;

    vector<int> controllers;

    vector<Player*> players;

    AudioPlayer* audioPlayer;

    int pistolShot;
    int warSounds;
    int music;

    int musicVolume = 128;
    int soundVolume = 128;

    void init() {
        Game::camera = new Auris::Camera(1280, 720);
        loadScene(&scene1);
        Engine::instance->world->SetGravity(b2Vec2(0, -9.8));

        audioPlayer = (AudioPlayer*) addEntity(make_shared<AudioPlayer>(nullptr, 5));
        music = audioPlayer->addMusic(AssetManager::getMusic("electronicMusic.wav"), 60);
        audioPlayer->playMusic(music);

        controllers.resize(8);
        for (auto & element : controllers) {
            element = -1;
        }
    }

    void earlyUpdate(float dt){

    }

    void update(float dt){

        int i = 0;
        vec2 camPos;
        for (auto & player : players) {
            camPos += vec2(player->transform->getPosition().x*Constants::METERS_TO_PIXELS, player->transform->getPosition().y*Constants::METERS_TO_PIXELS);
            i++;
        }

        if (i != 0) {
            camPos /= i;
            Game::camera->setPos(camPos);
        }

        if (Input::keyHeld(Action::m)) {
            audioPlayer->stopMusic();
        }
    }

    void lateUpdate(float dt){

    }

    void shutdown(){

    }

    void controllerConnected(){

    }

    void controllerActivated(int controllerID){
        int i = 0;
        for (auto & element : controllers) {
            if (element == -1) {
                element = controllerID;
                addPlayer(i, element);
                break;
            }
            i++;
        }
    }

    void addPlayer(int i, int controllerID){

        //Bow before Mathias' cancer vector
        vec2 pos = i == 0 ? vec2(-40, -10) :
                i == 1 ? vec2(-50, 30) :
                i == 2 ? vec2(40, -10) :
                i == 3 ? vec2(50, 30):
                vec2(0, 0);

        //Bow before Jonas' cancer vector
        vec4 col = i == 0 ? vec4(1,1,1,1) :
                   i == 1 ? vec4(0,1,0,1) :
                   i == 2 ? vec4(0,0,1,1) :
                   i == 3 ? vec4(1,0,1,1) :
                   vec4(1,1,1,1);

        auto player = (Player*) Game::instance->addEntity(make_shared<Player>(pos,col));
        player->setController(controllerID);
        player->name = player->type + to_string(controllerID);

        players.push_back(player);
    }


    void controllerDisconnected(int controllerID){
        int i = 0;
        for (auto & element : players) {
            if (element->controller == controllerID) {
                Game::destroyEntity(element);
                players.erase(players.begin() + i);
            }
            i++;
        }
    }

    void imGUI(){
    bool open = true;
        vec2 cameraPos = vec2(camera->getPos().x,camera->getPos().y);
        for(int i = 0; i<players.size();i++){

            vec2 playerPos = players[i]->transform->getPosition();

            vec2 labelPos = (cameraPos-playerPos)*Constants::METERS_TO_PIXELS;

            ImGui::SetNextWindowPos(ImVec2(labelPos.x,labelPos.y));
            ImGui::Begin("#TestLabel",&open,ImVec2(500,100),0,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoInputs);
            ImGui::Text("Hello, world!");
            ImGui::End();

            ImGui::SetNextWindowPos(ImVec2(0,0));
            ImGui::Begin("#TestLabel",&open,ImVec2(500,100),0,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoInputs);
            ImGui::Text("Hello, world!");
            ImGui::End();

            ImGui::SetNextWindowPos(ImVec2(100,100));
            ImGui::Begin("#TestLabel",&open,ImVec2(500,100),0,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoScrollbar|ImGuiWindowFlags_NoSavedSettings|ImGuiWindowFlags_NoInputs);
            ImGui::Text("Hello, world!");
            ImGui::End();
        }
    }
};
