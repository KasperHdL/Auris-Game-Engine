#pragma once

#include <SDL.h>
#include <SDL2/SDL_mixer.h>
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

//Engine
#include "Auris/Game.hpp"
#include "Auris/Entity.hpp"

#include "Auris/Utilities/MemoryLeakDetector.hpp"
#include "Auris/Utilities/Convert.hpp"

#include "Auris/Systems/Scene.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Systems/CollisionHandler.hpp"

#include "Auris/Action.hpp"
#include "Auris/Testing/ProfilingTimer.hpp"



namespace Auris{
class DebugUI;
class Engine{
public:
    Engine(int width, int height):width(width),height(height){}
    virtual ~Engine(){}

    void startup(Game* game);
    void shutdown();

    void run(SDL_Window* window);

    void HandleSDLEvents();

    static b2World* world;

    static void loadScene(Scene* scene);

    Game* game;

    SDL_Window *window;

    RenderSystem renderSystem;
    DebugUI* debugUI;

    b2ContactListener* collisionHandler;

    const int VELOCITY_ITERATIONS = 16;
    const int POSITION_ITERATIONS = 16;

    int width;
    int height;
 
    int quit;

	MemoryLeakDetector memLeakDet;

    ProfilingTimer profile_InputTimer;

    ProfilingTimer profile_Entity_UpdateTimer;

    ProfilingTimer profile_Game_EarlyUpdateTimer;
    ProfilingTimer profile_Game_UpdateTimer;
    ProfilingTimer profile_Game_LateUpdateTimer;

    ProfilingTimer profile_PhysicsTimer;
    ProfilingTimer profile_UpdatePhysicsEntityTransformTimer;

    ProfilingTimer profile_RenderTimer;
};
}
