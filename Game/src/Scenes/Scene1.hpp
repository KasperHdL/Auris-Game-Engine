#pragma once
 
#include "Auris/Engine.hpp"

#include "../Player.hpp"
#include "../Wall.hpp"
#include "../Test.hpp"
#include "../Bullet.hpp"
 
class Scene1 : public Auris::Scene {
public: 


    void init() { 
        name = "Scene 1";

        addGameObject(make_shared<Player>(vec2(20, 20)));
        addGameObject(make_shared<Test>(vec2(30,30)));
//        addGameObject(make_shared<Bullet>(vec2(-100, 10)));
        for (int i = -100; i < 140; i += 4)
            addGameObject(make_shared<Wall>(vec2(i, 0)));
    }
}; 
