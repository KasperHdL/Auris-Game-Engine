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

    vector<Player*> players;

    int pistolShot;
    int warSounds;

    int musicVolume = 128;
    int soundVolume = 128;

    void init() {
        camera = new Auris::Camera(1280, 720);
        loadScene(&scene1);
        Auris::Engine::world->SetGravity(b2Vec2(0, -9.8));

        controllers.resize(8);
        for (auto & element : controllers) {
            element = -1;
        }
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

    void controllerConnected(){

    }

    void controllerActivated(int controllerID){
        int i = 0;
        for (auto & element : controllers) {
            if (element == -1) {
                element = controllerID;
                vec2 pos = i == 0 ? vec2(-40, -10) : i == 1 ? vec2(-40, 30) : i == 2 ? vec2(40, -10) : i == 3 ? vec2(40, 30): vec2(0, 0);
                auto player = (Player*) addEntity(make_shared<Player>(pos));
                player->setController(controllerID);
                auto audio = (AudioPlayer*) addEntity(make_shared<AudioPlayer>(this->camera, 1));
                player->addChild(audio);
                players.push_back(player);
                break;
            }
            i++;
        }
    }


    void controllerDisconnected(int controllerID){
//        for (auto & element : players) {
//            if (element->controller == controllerID) {
//                delete element;
//            }
//        }
    }

    void imGUI(){

    }
};
