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
         * \param dt a float value. The current delta time in seconds.
        */
    virtual void earlyUpdate(float dt) = 0;

    //! The scriptable function update, taking 1 argument.
        /*!
         * Used by the game programmer to add update functionality to the game.
         * Called every frame in the update loop (Required to implement).
         * \param dt a float value. The current delta time in seconds.
        */
    virtual void update(float dt) = 0;

    //! The scriptable function lateUpdate, taking 1 argument.
        /*!
         * Used by the game programmer to add late update functionality to the game.
         * Called every frame late in the update loop (Required to implement).
         * \param dt a float value. The current delta time in seconds.
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
         * \sa controllerActivated(int controllerID)
        */
    virtual void controllerConnected(){}

    //! The scriptable function controllerActivated, taking 1 argument.
        /*!
         * Used by the game programmer to add functionality to when a controller is activated.
         * Called when a controller is activated (recognized with a button press).
         * \param controllerID an int value, that is the controller id of the controller activated.
         * \sa controllerConnected()
        */
    virtual void controllerActivated(int controllerID){}

    //! The scriptable function controllerDisconnected, taking 1 argument.
        /*!
         * Used by the game programmer to functionality to when a controller is disconnected.
         * Called when a controller is disconnected from the pc.
         * \param controllerID an int value, that is the controller id of the controller disconnected.
        */
    virtual void controllerDisconnected(int controllerID){}

    //! The scriptable function ImGui.
        /*!
         * Used by the game programmer to add GUI functionality to the game with imGui.
         * Called every frame, after the old gui has been cleared.
        */
    virtual void imGui(){}

    std::vector<std::shared_ptr<Entity>> entities; /*!< A vector value: entities, of shared pointers of Entity instances. Holds all entities of the game. */
    std::vector<int> destroyEntities; /*!< A vector value: destroyEntities, of integers. Holds the indexes of all gameobjects that are going to be destroyed this loop */
    std::vector<std::shared_ptr<Entity>> newEntities; /*!< A vector value: newEntities, of shared pointers of Entity instances. Holds the entities that are going to be added this loop */

    //! A method to add enitities to the game, taking 1 argument.
        /*!
         * Add the enity to the vector of all entities in the game
         * \param enity a shared_ptr of Entity. The entity that should be added to the game
         * \return Entity pointer. The entity that was added.
        */
    Entity* addEntity(std::shared_ptr<Entity> entity){
        newEntities.push_back(entity);
        entity.get()->init();
        return entity.get();
    }


    //! A method to load a scene, taking 1 argument.
        /*!
         * Loads the scene, and initialize the scene and all the enitities
         * \param scene a Scene pointer, that is the scene that should be loaded
        */
    void loadScene(Scene* scene){
        scene->init();
    }


    //! A method to destroy an entity, taking 1 argument.
        /*!
         * Loops through the static vector of entities in the game and marks
         * the entity and its children for destruction. Entities marked
         * for destructed are removed in the last call of the Engine::run loop.
         * \param entity an Entity pointer, the entity to be deleted.
        */
    void destroyEntity(Entity* entity) {
        int i = 0;
        for (auto & element : entities) {
            if (element.get() == entity) {
                destroyEntities.push_back(i);
                for (auto & child : element->children)
                    destroyEntity(child);
            }
            i++;
        }
    }
};
}
