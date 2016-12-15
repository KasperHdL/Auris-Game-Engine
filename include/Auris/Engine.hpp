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

//! The game engine class
    /*! Everything happens here!
    */
class Engine{
public:
    //! The engine contructor taking 2 arguments.
        /*!
          \param width an integer, that is the width of the window.
          \param height an interger, that is the height of the window.
        */
    Engine(int width, int height);

    //! The engine destructor.
        /*! Not used for anything, because when shutdown is run, everything is closed anyway
            \sa shutdown()
        */
    virtual ~Engine(){}

    //! A method to startup the engine, taking 1 argument.
        /*! Starts up all the engine systems
          \param game a Game pointer, that is the current game.
        */
    void startup(Game* game);

    //! A method to shutdown the engine.
        /*! Closes down all the engine systems */
    void shutdown();

    //! A method to run the engine, taking 1 argument.
        /*! This is the engine update, it runs once each frame
          \param window a SDL_Window pointer, that is the current window of the game.
        */
    void run(SDL_Window* window);

    static b2World* world; /*!< A static b2World pointer: world. A reference to the physics world */

    Game* game; /*!< A Game pointer: game. A reference to the current game */

    SDL_Window *window; /*!< A SDL_Window pointer: window. A reference to the current window */

    RenderSystem renderSystem; /*!< A Rendersystem value: renderSystem. The rendersystem of the engine */
    DebugUI* debugUI; /*!< A DebugUI pointer: debugUI. A reference to the current engine debugUI */

    b2ContactListener* collisionHandler; /*!< A b2ContactListener pointer: collisionHandler. A reference to the box2d contactlistener, handling collision */

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
