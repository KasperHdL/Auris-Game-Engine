#pragma once
 
#include "Auris/Engine.hpp"
#include "Auris/Entities/Light.hpp"
#include "Auris/Utilities/AudioPlayer.hpp"

#include "../Player.hpp"
#include "../Wall.hpp"
#include "../Bullet.hpp"
 
class Scene1 : public Auris::Scene {
public: 
    void init() {
        Game::instance->addEntity(make_shared<Auris::Light>(vec2(20,20)));
        Game::instance->addEntity(make_shared<Wall>(vec2(-64, 0),1,25,"wall"));
        Game::instance->addEntity(make_shared<Wall>(vec2(64, 0),1,25, "wall"));
        Game::instance->addEntity(make_shared<Wall>(vec2(0, 35),40,1,"jumpable"));
        Game::instance->addEntity(make_shared<Wall>(vec2(0, -35),40,1, "jumpable"));

        Game::instance->addEntity(make_shared<Wall>(vec2(0, 0),10,1, "jumpable"));
    }
}; 
