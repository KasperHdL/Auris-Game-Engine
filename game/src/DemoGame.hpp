#pragma once

#include "../../engine/src/Auris.hpp"
#include "../data/level1.hpp"
#include "../data/level2.hpp"

class DemoGame : public Game {
    Keys keys;
    Level1 level1;
    Level2 level2;


    void init() {
        keys.setKey("space", SDL_SCANCODE_SPACE);

        Auris::loadScene(&level1);
        for (auto & el : RenderSystem::animations)
            cout << "Animation after load: " << &el << endl;
    }

    void earlyUpdate(float dt){

    }

    void update(float dt){

    }

    void lateUpdate(float dt){
        if (Input::keyDown(keys.getKey("space"))){

            Auris::loadScene(&level2);
        }
    }

    void shutdown(){

    }
};
