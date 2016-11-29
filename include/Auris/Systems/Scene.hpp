#pragma once

#include "Auris/GameObjects/GameObject.hpp"
#include <vector>


namespace Auris{
class Scene {
public:
    string name;

    vector<shared_ptr<GameObject>> gameObjects;

    void addGameObject(shared_ptr<GameObject> gameObject){
        gameObjects.push_back(gameObject);
    }

    void unload() {
        gameObjects.clear();
    }


    virtual void init() {}
};
}
