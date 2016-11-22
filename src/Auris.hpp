#pragma once

#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"
#include "Box2D/Box2D.h"

#include <memory>
#include <vector>
#include "GameObjects/GameObject.hpp"
#include <iostream>

#include "Game.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/ParticleSystem.hpp"
#include "Utility/MemoryLeakDetector.hpp"
#define SDL_MAIN_HANDLED

#include "Testing/Showcases/ShowcasePanel.hpp"
#include "Testing/DebugDraw.hpp"

#include "Systems/Input.hpp"
#include "Systems/CollisionHandler.hpp"
#include "SRE/SimpleRenderEngine.hpp"

#include "SRE/imgui_sre.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <SDL.h>

class DebugDraw;

class Auris{
public:
    Auris(int width, int height):width(width),height(height){}
    virtual ~Auris(){}

    void startup(Game* game);
    void shutdown();

    void run(SDL_Window* window);

    void HandleSDLEvents();

    static b2World* world;

    static void addGameObject(shared_ptr<GameObject> gameObject);

private:
    Game* game;

    SDL_Window *window;

    static vector<shared_ptr<GameObject>> gameObjects;
    RenderSystem renderSystem;
    ShowcasePanel showcasePanel;

    b2ContactListener* collisionHandler;
    vec2 camPos;

    const int VELOCITY_ITERATIONS = 16;
    const int POSITION_ITERATIONS = 16;

    bool debug = false;
    bool pause = false;

    int width;
    int height;
 
    int quit;

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

	MemoryLeakDetector memLeakDet;

    inline glm::vec2 toGlm(const b2Vec2 &v) {
            return glm::vec2(v.x, v.y);
    }
    inline b2Vec2 toB2(const glm::vec2 v){
        return b2Vec2(v.x,v.y);
    }
};


