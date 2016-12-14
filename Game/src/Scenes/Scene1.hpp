#pragma once 
 
#include "Auris/Engine.hpp"

#include "../Player.hpp"
#include "../Wall.hpp"
#include "../Test.hpp"
 
class Scene1 : public Auris::Scene {
public: 
    void init(Game* game) { 
        game->addEntity(make_shared<Player>(vec2(20, 20)));
        game->addEntity(make_shared<Test>(vec2(30,30)));
            game->addEntity(make_shared<Wall>(vec2(20, 0)));
            game->addEntity(make_shared<Wall>(vec2(0, 0)));
        //for (int i = 0; i < 155; i += 5)
         //   game->addEntity(make_shared<Wall>(vec2(i, 100)));
    }
}; 
