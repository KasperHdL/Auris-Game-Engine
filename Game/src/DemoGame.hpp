#pragma once

#include "Auris/Engine.hpp"

#include "Scenes/Scene1.hpp"
#include "Scenes/Scene2.hpp"

class DemoGame : public Auris::Game {
    Auris::Keys keys;
    Scene1 scene1;
    Scene2 scene2;


    void init() {
        keys.setKey("space", SDL_SCANCODE_SPACE);

        Auris::Engine::loadScene(&scene1);
        for (auto & el : Auris::RenderSystem::animations)
            cout << "Animation after load: " << &el << endl;
    }

    void earlyUpdate(float dt){

    }

    void update(float dt){

    }

    void lateUpdate(float dt){
        if (Auris::Input::keyDown(keys.getKey("space"))){

           Auris::Engine::loadScene(&scene2);
        }
    }

    void shutdown(){

    }
};
