#pragma once

#include "Auris/Entities/Nuggets/Transform.hpp"
#include <string>


namespace Auris{

//! The entity class
    /*! Have basic information about entities, every entity except the camera inherents from this class
    */
class Entity{
public:
    std::string name = "";/*!< A string value: name. The name of the entity. */  
    Entity* parent = nullptr;/*!< An Entity pointer: parent. An pointer to the parent entity of this entity. */
    Entity* child = nullptr;/*!< An Entity pointer: child. A pointer to the parent entity of this entity.*/
    Transform* transform; /*!< A Transform pointer: transform. An instance of the transform. */

    //! The engine contructor.
        /*!
         * Declares a new Transform.
        */
    Entity(){
        transform = new Transform(this);
    }

    //! The engine destructor.
        /*!
         * Deletes the Transform pointer.
        */
    ~Entity(){
        delete transform;
    }


    //! The scriptable function updateTransform.
        /*!
         * Updates the enitities transform according to the physics body
         * Should not be used by the game programmer
        */
    virtual void updateTransform(){}

    //! The scriptable function init.
        /*!
         * Used by the game programmer to add initial functionality to the enitity
         * Called upon initialization
        */
    virtual void init() {}

    //! The scriptable function start.
        /*!
         * Used by the game programmer to add start functionality to the enitity
         * Called just before first update
        */
    virtual void start() {}

    //! The scriptable function update, taking 1 argument
        /*!
         * Used by the game programmer to add update functionality to the enitity
         * Called every frame
          \param deltaTime a float value, that is the current delta time
        */
    virtual void update(float deltaTime) {}

    //! The scriptable function onDestruction.
        /*!
         * Used by the game programmer to add on destruction functionality to the enitity
         * Called when the object is destroyed
        */
    virtual void onDestruction() {}

};


}
