#pragma once 
 
#include "Auris/Engine.hpp"

#include "../Player.hpp"
#include "../Wall.hpp"
 
class Scene1 : public Auris::Scene {
public: 
    void init() { 
        name = "Scene 1";
 
        addGameObject(make_shared<Player>(vec2(10, 10)));
        for (int i = 0; i < 200; i + 10)
            addGameObject(make_shared<Wall>(vec2(0, i)));
    } 
}; 
