#pragma once 
 
#include "Auris/Engine.hpp"
#include "Auris/Systems/Scene.hpp"
#include "../Player.hpp"
#include "../Wall.hpp"
 
class Scene2 : public Auris::Scene {
public: 
    void init(Game* game) { 
        game->addEntity(make_shared<Player>(vec2(10, 10)));
        game->addEntity(make_shared<Player>(vec2(10, 20)));
        game->addEntity(make_shared<Wall>(vec2(10, 30)));
        game->addEntity(make_shared<Player>(vec2(10, 40)));
    } 
}; 
