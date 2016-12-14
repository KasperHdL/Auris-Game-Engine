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

//Engine
#include "Auris/Game.hpp"
#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/Utilities/MemoryLeakDetector.hpp"
#include "Auris/Utilities/Convert.hpp"
#include "Auris/GameObjects/Camera.hpp"

#include "Auris/Systems/Scene.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Systems/CollisionHandler.hpp"


#include "Auris/Action.hpp"


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

    static Scene* currentScene;

    static void loadScene(Scene* scene);
    static void removeGameObject(GameObject* gameObject);

    Game* game;

    SDL_Window *window;

    RenderSystem renderSystem;
    DebugUI* debugUI;

    b2ContactListener* collisionHandler;
    vec2 camPos;

    const int VELOCITY_ITERATIONS = 16;
    const int POSITION_ITERATIONS = 16;

    int width;
    int height;
 
    int quit;

	MemoryLeakDetector memLeakDet;


};
}
