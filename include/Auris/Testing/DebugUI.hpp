#pragma once

#include "Auris/Testing/DebugDraw.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Utilities/MemoryLeakDetector.hpp"
#include <vector>

/*!
 * DebugUI allows the Engine to draw an Debug overlay to show debug information for the engine.
 *
 */


namespace Auris{
class Engine;
class DebugUI{
private:
    Engine* e;
    friend class Engine;

    DebugDraw debugDraw;

    bool drawDebug = false; //!< will call drawDebug on entities
    bool drawColliders = false;//!< will draw box2d DebugDraw

  
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


    //Profiling
    float arr_profInput[arrSize] = {};
    float arr_profEntityUpdate[arrSize] = {};
    float arr_profGEarlyUpdate[arrSize] = {};
    float arr_profGUpdate[arrSize] = {};
    float arr_profGLateUpdate[arrSize] = {};
    float arr_profPhysics[arrSize] = {};
    float arr_profUpdateTransform[arrSize] = {};
    float arr_profRender[arrSize] = {};


    //Toggles
    bool toggle_goInspector = false;
    bool toggle_cameraControls = false;

    enum InspectorMode{
        Closed,
        Open,

    };

    static const int entityInspectorOpenSize = 1024;
    bool entityInspectorOpen[entityInspectorOpenSize] = {false};

    MemoryLeakDetector memLeakDet;


public:
    bool debug = false;//!< turn on or off debug
    bool pause = false;//!< pause the engine(is read by the \see Auris::Engine
    bool runOneStep = false;//!< run one frame and pause
    bool profiling = false;//!< run profiling in engine update loop
 
    DebugUI(){}

    void startup(Engine* engine);
    void shutdown();
    void update(float dt);
    void draw();
};
}
