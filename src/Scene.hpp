#pragma once

#include "GameObject.hpp"
#include <vector>
#include <memory>
#include "Box2D/Box2D.h"

using namespace std;
class Scene{
    public:
        vector<shared_ptr<GameObject>> gameObjects;


        b2World* world;

        const int VELOCITY_ITERATIONS = 16;
        const int POSITION_ITERATIONS = 16;

        Scene(){
            gameObjects.reserve(64);

            world = new b2World(toB2(glm::vec2(0,-10)));

        }

        ~Scene(){
            delete world;
            world = nullptr;
            gameObjects.clear();
        }

        void update(float dt){

            world->Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

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

        inline glm::vec2 toGlm(const b2Vec2 &v) {
                return glm::vec2(v.x, v.y);
        }
        inline b2Vec2 toB2(const glm::vec2 v){
            return b2Vec2(v.x,v.y);
        }
};

