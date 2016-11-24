#pragma once

#include "Player.hpp"
#include "Wall.hpp"
#include "Auris/Game.hpp"

class DemoGame : public Game {

    void init() {
        Auris::addGameObject(make_shared<Player>(vec2(10,10)));
        Auris::addGameObject(make_shared<Player>());
        Auris::addGameObject(make_shared<Wall>(vec2(30,30)));
    }

    void earlyUpdate(float dt){

    }

    void update(float dt){

    }

    void lateUpdate(float dt){

    }

    void shutdown(){

    }
};
