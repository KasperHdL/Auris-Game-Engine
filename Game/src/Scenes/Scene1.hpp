#pragma once 
 
#include "Auris/Engine.hpp"

#include "../Player.hpp"
#include "../Wall.hpp"
 
class Scene1 : public Auris::Scene {
public: 
    void init() { 
        name = "Scene 1";
 
        addGameObject(make_shared<Player>(vec2(10, 10)));
        addGameObject(make_shared<Player>(vec2(20, 10)));
        addGameObject(make_shared<Player>(vec2(30, 10)));
        addGameObject(make_shared<Player>(vec2(40, 10)));
    } 
}; 
