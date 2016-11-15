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
#include "Systems/ParticleSystem.hpp"
#include "MemoryLeakDetector.hpp"

class DebugDraw;
class Engine{
public:
    Engine(int width, int height):width(width),height(height){};
    virtual ~Engine(){};

    void startup(SDL_Window* window);
    void shutdown();

    void run(SDL_Window* window);

    void HandleSDLEvents();

private:

    vector<shared_ptr<GameObject>> gameObjects;
    RenderSystem renderSystem;
    ParticleSystem particleSystem;

    b2World* world;
    vec2 camPos;

    const int VELOCITY_ITERATIONS = 16;
    const int POSITION_ITERATIONS = 16;

    bool debug = false;
    bool pause = false;

    int width;
    int height;
 
    int quit;


	MemoryLeakDetector memLeakDet;

    inline glm::vec2 toGlm(const b2Vec2 &v) {
            return glm::vec2(v.x, v.y);
    }
    inline b2Vec2 toB2(const glm::vec2 v){
        return b2Vec2(v.x,v.y);
    }
};


