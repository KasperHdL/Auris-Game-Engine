#pragma once

#include <SDL.h>
#define SDL_MAIN_HANDLED

#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"
#include "SRE/imgui_sre.hpp"

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Box2D/Box2D.h"

#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

//Auris
#include "Auris/Game.hpp"
#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/Utility/MemoryLeakDetector.hpp"
#include "Auris/Utility/Convert.hpp"

#include "Auris/Systems/Input.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Systems/ParticleSystem.hpp"
#include "Auris/Systems/CollisionHandler.hpp"

#include "Auris/Testing/Showcases/ShowcasePanel.hpp"
#include "Auris/Testing/DebugDraw.hpp"


class DebugDraw;

class Engine{
public:
    Engine(int width, int height):width(width),height(height){}
    virtual ~Engine(){}

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


};

