#pragma once

#include "Auris/Engine.hpp"

#include "Scenes/Scene1.hpp"
#include "Scenes/Scene2.hpp"

class DemoGame : public Auris::Game {
    Scene1 scene1;

    int id1 = -1;
    int id2 = -1;
    void init() {
        Auris::Engine::loadScene(&scene1);
        Auris::Engine::world->SetGravity(b2Vec2(0, -9.8));
    }

    void earlyUpdate(float dt){

    }

    void update(float dt){

        if(id1!=-1){
          cout << id1 << ": " << Input::getControllerAxisState(id1,SDL_CONTROLLER_AXIS_TRIGGERRIGHT) << endl;
        }
        if(id2!=-1){
            cout << id2 << ": " << Input::getControllerAxisState(id2,SDL_CONTROLLER_AXIS_TRIGGERRIGHT) << endl;
        }

    }

    void lateUpdate(float dt){

    }

    void shutdown(){

    }

    void controllerConnected(int controllerID){
        if(id1==-1){
            id1 = controllerID;
        }else{
            id2 = controllerID;
        }
    }

    void controllerDisconnected(int controllerID){

    }
};
