#pragma once
 
#include "Auris/Engine.hpp"
#include "Auris/Entities/Light.hpp"

#include "../Player.hpp"
#include "../Wall.hpp"
#include "../Bullet.hpp"
 
class Scene1 : public Auris::Scene {
public: 
    void init(Game* game) { 
        game->addEntity(make_shared<Player>(vec2(20, 20)));
        game->addEntity(make_shared<Auris::Light>(vec2(20,20)));
            game->addEntity(make_shared<Wall>(vec2(20, 0)));
            game->addEntity(make_shared<Wall>(vec2(0, 0)));
        //for (int i = 0; i < 155; i += 5)
         //   game->addEntity(make_shared<Wall>(vec2(i, 100)));
    }
}; 
