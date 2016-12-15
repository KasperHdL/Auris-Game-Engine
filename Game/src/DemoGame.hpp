#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Entities/Camera.hpp"

#include "Scenes/Scene1.hpp"
#include "Scenes/Scene2.hpp"
#include "Auris/Utilities/AudioPlayer.hpp"

using namespace Auris;

class DemoGame : public Auris::Game {
    Scene1 scene1;
    AudioPlayer audioPlayer;
    Auris::Camera* camera;

    int pistolShot;
    int warSounds;

    int musicVolume = 128;
    int soundVolume = 128;

    int id1 = -1;
    int id2 = -1;
    int id3 = -1;
    void init() {
        loadScene(&scene1);
        Auris::Engine::world->SetGravity(b2Vec2(0, -9.8));
        pistolShot = audioPlayer.addSound(AssetManager::getDataPath("pistolShot.wav").c_str(), 128);
        warSounds = audioPlayer.addMusic(AssetManager::getDataPath("warSounds.wav").c_str(), 128);
        audioPlayer.playMusic(warSounds);
        camera = new Auris::Camera(1280, 720);
    }

    void earlyUpdate(float dt){

    }

    void update(float dt){
        if (Input::keyDown(SDL_SCANCODE_RETURN))
            audioPlayer.playSound(pistolShot);

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

    void controllerConnected(int controllerID){
        if(id1==-1){
            id1 = controllerID;
        }else if(id2==-1){
            id2 = controllerID;
        }else if(id3==-1){
            id3 = controllerID;
        }
    }

    void controllerDisconnected(int controllerID){
        if(id1==controllerID){
            id1 = -1;
        }else if(id2==controllerID){
            id2 = -1;
        }else if(id3==controllerID){
            id3 = -1;
        }
    }
};
