#pragma once 
 
#include "Auris/Engine.hpp"

#include "../Player.hpp"
#include "../Wall.hpp"
#include "../Test.hpp"
 
class Scene1 : public Auris::Scene {
public: 
    void init() { 
        name = "Scene 1";

        addGameObject(make_shared<Player>(vec2(20, 20)));
        addGameObject(make_shared<Test>(vec2(30,30)));
        for (int i = 0; i < 155; i += 4)
            addGameObject(make_shared<Wall>(vec2(i, 0)));
    }


}; 
