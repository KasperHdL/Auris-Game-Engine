#pragma once
#include "Auris/Auris.hpp"

#include "../Player.hpp"
#include "../Wall.hpp"
#include "../Bullet.hpp"
 
class Scene1 : public Auris::Scene {
public: 
    void init() {
        Game::instance->addEntity(make_shared<Auris::Light>(vec2(20,20)));
        Game::instance->addEntity(make_shared<Wall>(vec2(-64, 0),1,25,"wall"));
        Game::instance->addEntity(make_shared<Wall>(vec2(64, 0),1,25, "wall"));
        Game::instance->addEntity(make_shared<Wall>(vec2(0, 35),40,1,"roof"));
        Game::instance->addEntity(make_shared<Wall>(vec2(0, -35),40,1, "jumpable"));

        Game::instance->addEntity(make_shared<Wall>(vec2(0, 0),10,1, "jumpable"));

        Game::instance->addEntity(make_shared<Wall>(vec2(-40, -20),4,1, "jumpable"));
        Game::instance->addEntity(make_shared<Wall>(vec2(40, -20),4,1, "jumpable"));

        Game::instance->addEntity(make_shared<Wall>(vec2(-50, 23),5,2, "jumpable"));
        Game::instance->addEntity(make_shared<Wall>(vec2(50, 23),5,2, "jumpable"));

        Game::instance->addEntity(make_shared<Wall>(vec2(31, 10),2,1, "jumpable"));
        Game::instance->addEntity(make_shared<Wall>(vec2(-31, 10),2,1, "jumpable"));


        Game::instance->addEntity(make_shared<Wall>(vec2(0, -22),1,7, "jumpable"));
    }
}; 
