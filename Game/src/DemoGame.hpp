#pragma once

#include "Auris/Engine.hpp"

#include "Scenes/Scene1.hpp"
#include "Scenes/Scene2.hpp"

class DemoGame : public Game {
    Keys keys;
    Scene1 scene1;
    Scene2 scene2;


    void init() {
        keys.setKey("space", SDL_SCANCODE_SPACE);

        Engine::loadScene(&scene1);
        for (auto & el : RenderSystem::animations)
            cout << "Animation after load: " << &el << endl;
    }

    void earlyUpdate(float dt){

    }

    void update(float dt){

    }

    void lateUpdate(float dt){
        if (Input::keyDown(keys.getKey("space"))){

            Engine::loadScene(&scene2);
        }
    }

    void shutdown(){

    }
};
