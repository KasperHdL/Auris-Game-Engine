#pragma once

#include "GameObject.hpp"
#include <vector>
#include <memory>

using namespace std;
class Scene{
    public:
        vector<shared_ptr<GameObject>> gameObjects;


        Scene(){
            gameObjects.reserve(64);

        }

        ~Scene(){

        }

        void update(float dt){
            for(auto& g : gameObjects)
                g->update(dt);
        }

        void draw(){
            for(auto& g : gameObjects)
                g->draw();
        }

        void add(shared_ptr<GameObject> g){
            gameObjects.push_back(g);

        }
};

