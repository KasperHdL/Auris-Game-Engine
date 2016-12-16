#pragma once

#include "Auris/Testing/DebugDraw.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Utilities/MemoryLeakDetector.hpp"
#include <vector>

namespace Auris{
class Engine;

//! The DebugUI class
    /*! Allows the Engine to draw an Debug overlay to show debug information for the engine.
    */
class DebugUI{
private:
    Engine* e; /*!< An Engine pointer: e. An instance of the engine. */
    friend class Engine;

    DebugDraw debugDraw; /*!< A DebugDraw value: debugDraw. The DebugDraw object, used to draw stuff. */

    bool drawDebug = false; /*!< A bool value: drawDebug. Will call drawDebug on entities */
    bool drawColliders = false; /*!< A bool value: drawColliders. Will draw box2d DebugDraw */

  
    //Following is to manage plots for dt, mem
    int arrIndex = 0; /*!< An int value: arrIndex. Index of the array */
    static const int arrSize = 600; /*!< A static constant int value: arrSize. Size of the array */

    float arr_deltaTime[arrSize] = {}; /*!< A float array: arr_deltaTime. Array for delta time */
    float max_deltaTime = 0; /*!< A float value: max_deltaTime. Max of delta time */

    
    float arr_virtMem[arrSize] = {}; /*!< A float array: arr_virtMem. Array for virtual memory */
    float max_virtMem = 0; /*!< A float value: max_virtMem. Max of virtual memory */

    float arr_physMem[arrSize] = {}; /*!< A float array: arr_physMem. Array for physical memory */
    float max_physMem = 0; /*!< A float value: max_physMem. Max of physical memory */

    int max_renderSprites = 0; /*!< A float value: max_renderSprites. Max of rendered sprites */


    //Profiling
    float arr_profInput[arrSize] = {}; /*!< A float array: arr_profInput. Array for profiling input loop */
    float arr_profEntityUpdate[arrSize] = {}; /*!< A float array: arr_EnitityUpdate. Array for profiling Entity update loop */
    float arr_profGEarlyUpdate[arrSize] = {}; /*!< A float array: arr_profGEarlyUpdate. Array for profiling the game early update loop */
    float arr_profGUpdate[arrSize] = {}; /*!< A float array: arr_profGUpdate. Array for profiling the game update loop */
    float arr_profGLateUpdate[arrSize] = {}; /*!< A float array: arr_profGLateUpdate. Array for profiling the game late update loop */
    float arr_profPhysics[arrSize] = {}; /*!< A float array: arr_profPhysics. Array for profiling physics loop */
    float arr_profUpdateTransform[arrSize] = {}; /*!< A float array: arr_profUpdateTransform. Array for profiling transform update loop */
    float arr_profRender[arrSize] = {}; /*!< A float array: arr_profRender. Array for profiling render loop */


    //Toggles
    bool toggle_inspector = false;
    bool toggle_hierarchy = false;
    bool toggle_cameraControls = false;
    bool toggle_goInspector = false; /*!< A bool value: toggle_goInspector. Toggle the inspector view */
    bool toggle_cameraControls = false; /*!< A bool value: toggle_cameraControls. Toggle the camera controls */

    //! An enum of DebugUI::InspectorMode.
    /*! That holds information about in which mode of inspector.
     * Close and Open
     */
    enum InspectorMode{
        Closed,
        Open,

    };

    static const int entityInspectorOpenSize = 1024; /*!< A static constant int value: entityInspectorOpenSize. The size of the entity inspector on open */
    bool entityInspectorOpen[entityInspectorOpenSize] = {false}; /*!< A bool value: entityInspectorOpen. If the entity inspector is open or not */

    MemoryLeakDetector memLeakDet; /*!< A MemeoryLeadDetector value: menLeadDet. Used for the detection of memory leaks */


public:
    bool debug = false;/*!< A bool value: debug. Turn on or off debug */
    bool pause = false; /*!< A bool value: pause. Pause the engine (is read by the \sa Auris::Engine::run) */
    bool runOneStep = false;/*!< A bool value: runOneStep. Run one frame and pause */
    bool profiling = false;/*!< A bool value: profiling. Run profiling in engine update loop */
 
    //! The DebugUI constructor.
        /*!
         * Does nothing.
        */
    DebugUI(){}

    //! A startup method, taking 1 argument.
        /*! Initializes the DebugUI, starts ImGui and sets required keys for debug input
         * \param engine an Engine pointer. An instance of the Engine.
        */
    void startup(Engine* engine);

    //! A shutdown method.
        /*! Does nothing.
        */
    void shutdown();

    //! An update method, taking 1 argument.
        /*! updates ImGui, saves deltatime and memory.
         * \param dt a float value. The delta time in seconds.
        */
    void update(float dt);

    //! A draw method.
        /*!  calls debugdraw on entities and draws box2d debug if drawdebug and draw colliders is enabled respectively.
        */
    void draw();
};
}
