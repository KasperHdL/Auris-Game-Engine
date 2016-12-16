#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Systems/Scene.hpp"
#include "Auris/Entity.hpp"
#include "Auris/Entities/Camera.hpp"
#include <vector>
#include <memory>

namespace Auris{

//! The game class.
    /*! Used to create a new game of the engine.
     * The game programmer should extend this class to create a new game.
    */
class Game {

public:
    static Game* instance;
    Game();

    Camera* camera; /*!< An Auris::Camera pointer. A reference to a camera, can be used to control the game camera. */

    //! The scriptable function init.
        /*!
         * Used by the game programmer to add initial functionality to the game.
         * Called upon initialization (Required to implement).
        */
    virtual void init() = 0;

    //! The scriptable function earlyUpdate, taking 1 argument.
        /*!
         * Used by the game programmer to add early update functionality to the game.
         * Called every frame early in the update loop (Required to implement).
         * \param dt a float value, that is the current delta time.
        */
    virtual void earlyUpdate(float dt) = 0;

    //! The scriptable function update, taking 1 argument.
        /*!
         * Used by the game programmer to add update functionality to the game.
         * Called every frame in the update loop (Required to implement).
         * \param dt a float value, that is the current delta time.
        */
    virtual void update(float dt) = 0;

    //! The scriptable function lateUpdate, taking 1 argument.
        /*!
         * Used by the game programmer to add late update functionality to the game.
         * Called every frame late in the update loop (Required to implement).
         * \param dt a float value, that is the current delta time.
        */
    virtual void lateUpdate(float dt) = 0;

    //! The scriptable function drawDebugImGui.
        /*!
         * Used by the game programmer to add debug imgui functionality to the game.
         * Called every frame, when the engine debug imgui is drawed.
        */
    virtual void drawDebugImGui(){}

    //! The scriptable function shutdown.
        /*!
         * Used by the game programmer to add shutdowm functionality to the game.
         * Called when the game is shutdown (Required to implement).
        */
    virtual void shutdown() = 0;

    //! The scriptable function controllerConnected.
        /*!
         * Used by the game programmer to add functionality to when a controller is connected.
         * Called when a controller is connected to the pc.
        */
    virtual void controllerConnected(){}

    //! The scriptable function controllerActivated, taking 1 argument.
        /*!
         * Used by the game programmer to add functionality to when a controller is activated.
         * Called when a controller is activated (recognized with a button press).
         * \param controllerID an int value, that is the controller id of the controller activated.
        */
    virtual void controllerActivated(int controllerID){}

    //! The scriptable function controllerDisconnected, taking 1 argument.
        /*!
         * Used by the game programmer to functionality to when a controller is disconnected.
         * Called when a controller is disconnected from the pc.
         * \param controllerID an int value, that is the controller id of the controller disconnected.
        */
    virtual void controllerDisconnected(int controllerID){}

    //! The scriptable function imGUI.
        /*!
         * Used by the game programmer to add GUI functionality to the game with imgui.
         * Called every frame, after the old gui has been cleared.
        */
    virtual void imGUI(){}

    std::vector<std::shared_ptr<Entity>> entities; /*!< A vector value: entities, of shared pointers of Entity instances. Holds all entities of the game. */

    //! A method to add enitities to the game, taking 1 argument.
        /*!
         * Add the enity to the vector of all entities in the game
         * \param enity a shared_ptr of Entity, that is the entity that should be added to the game
        */
    Entity* addEntity(std::shared_ptr<Entity> entity){
        entities.push_back(entity);
        return entity.get();
    }


    //! A method to load a scene, taking 1 argument.
        /*!
         * Loads the scene, and initialize the scene and all the enitities
         * \param scene a Scene pointer, that is the scene that should be loaded
        */
    void loadScene(Scene* scene){
        scene->init();

        for (auto & el : entities)
            el->init();
    }

};
}
