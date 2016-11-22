#pragma once

#include "GameObjects/Player.hpp"
#include "GameObjects/Wall.hpp"
#include "Game.hpp"

class DemoGame : public Game {
    void init() {
        Auris::addGameObject(make_shared<Player>(Auris::world,vec2(10,10)));
        Auris::addGameObject(make_shared<Player>(Auris::world));
        Auris::addGameObject(make_shared<Wall>(Auris::world,vec2(30,30)));
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
