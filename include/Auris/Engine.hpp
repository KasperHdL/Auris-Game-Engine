#pragma once

#ifdef _WIN32 // Windows
#include <SDL_mixer.h>
#elif __linux__ // Linux
#include <SDL2/SDL_mixer.h>
#else
cout << "Error: Unsupported OS" << endl;
#endif

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

#include "algorithm"

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

    ProfilingTimer profile_InputTimer; /*!< A ProfilingTimer value: profile_InputTimer. The profile timer to handle the input loop */

    ProfilingTimer profile_Entity_UpdateTimer; /*!< A ProfilingTimer value: profile_Entity_UpdateTimer. The profile timer to handle the entity update loop */

    ProfilingTimer profile_Game_EarlyUpdateTimer; /*!< A ProfilingTimer value: profile_Game_EarlyUpdateTimer. The profile timer to handle the game early update loop */
    ProfilingTimer profile_Game_UpdateTimer; /*!< A ProfilingTimer value: profile_Game_UpdateTimer. The profile timer to handle the game update loop */
    ProfilingTimer profile_Game_LateUpdateTimer; /*!< A ProfilingTimer value: profile_Game_LateUpdateTimer. The profile timer to handle the game late update loop */

    ProfilingTimer profile_PhysicsTimer; /*!< A ProfilingTimer value: profile_PhysicsTimer. The profile timer to handle the physics loop */
    ProfilingTimer profile_UpdatePhysicsEntityTransformTimer; /*!< A ProfilingTimer value: profile_UpdatePhysicsEntityTransformTimer. The profile timer to handle the physics entity transform update loop */

    ProfilingTimer profile_RenderTimer; /*!< A ProfilingTimer value: profile_RenderTimer. The profile timer to handle the render loop */
    ProfilingTimer profile_SwapTimer; /*!< A ProfilingTimer value: profile_RenderTimer. The profile timer to handle the render loop */
};
}
