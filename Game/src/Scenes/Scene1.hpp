#pragma once
 
#include "Auris/Engine.hpp"
#include "Auris/Entities/Light.hpp"
#include "Auris/Utilities/AudioPlayer.hpp"

#include "../Player.hpp"
#include "../Wall.hpp"
#include "../Bullet.hpp"
 
class Scene1 : public Auris::Scene {
public: 
    void init(Game* game) { 
        game->addEntity(make_shared<Auris::Light>(0,vec2(20,20)));
        game->addEntity(make_shared<Wall>(vec2(-40, -20)));
        game->addEntity(make_shared<Wall>(vec2(-40, 20)));
        game->addEntity(make_shared<Wall>(vec2(40, -20)));
        game->addEntity(make_shared<Wall>(vec2(40, 20)));
    }
}; 
