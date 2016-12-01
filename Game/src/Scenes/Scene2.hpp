#pragma once 
 
#include "Auris/Engine.hpp"
#include "Auris/Systems/Scene.hpp"
#include "../Player.hpp"
#include "../Wall.hpp"
 
class Scene2 : public Auris::Scene {
public: 
    void init() { 
        name = "Scene 2";
 
        addGameObject(make_shared<Player>(vec2(10, 10)));
        addGameObject(make_shared<Player>(vec2(10, 20)));
        addGameObject(make_shared<Player>(vec2(10, 30)));
        addGameObject(make_shared<Player>(vec2(10, 40)));
    } 
}; 
