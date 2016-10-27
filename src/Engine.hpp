#pragma once

#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"
#include "SDL.h"
#include "Box2D/Box2D.h"

#include <memory>
#include <vector>
#include "GameObjects/GameObject.hpp"
#include <iostream>

#include "RenderSystem.hpp"

class DebugDraw;
class Engine{
public:
    Engine(int width, int height):width(width),height(height){};
    virtual ~Engine(){};

    void startup();
    void shutdown();

    void run();

    void HandleSDLEvents();

private:

    vector<shared_ptr<GameObject>> gameObjects;
    RenderSystem renderSystem;

    b2World* world;

    const int VELOCITY_ITERATIONS = 16;
    const int POSITION_ITERATIONS = 16;

    int width;
    int height;
 
    int quit;

    inline glm::vec2 toGlm(const b2Vec2 &v) {
            return glm::vec2(v.x, v.y);
    }
    inline b2Vec2 toB2(const glm::vec2 v){
        return b2Vec2(v.x,v.y);
    }
};


