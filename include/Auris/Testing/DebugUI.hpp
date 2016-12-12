#pragma once

#include "Auris/Testing/DebugDraw.hpp"
#include "Auris/Systems/Input.hpp"

/*!
 * DebugUI allow the Engine to draw an Debug overlay to show debug information for the engine.
 *
 */


namespace Auris{
class Engine;
class DebugUI{
private:
    Engine* e;
    friend class Engine;

    DebugDraw debugDraw;

    Keys keys;

    bool drawDebug = false; //!< will draw box2d DebugDraw

  
    //Following is to manage plots for dt, mem
    int arrIndex = 0;
    static const int arrSize = 600;

    float arr_deltaTime[arrSize] = {};
    float max_deltaTime = 0;

    
    float arr_virtMem[arrSize] = {};
    float max_virtMem = 0;

    float arr_physMem[arrSize] = {};
    float max_physMem = 0;

    int max_renderSprites = 0;

    //Toggles
    bool toggle_goInspector = false;
    bool toggle_cameraControls = false;


public:
    bool debug = false;//!< turn on or off debug
    bool pause = false;//!< pause the engine(is read by the \see Auris::Engine
    bool runOneStep = false;//!< run one frame and pause
 
    DebugUI(){}

    void startup(Engine* engine);
    void shutdown();
    void update(float dt);
    void draw();
};
}
