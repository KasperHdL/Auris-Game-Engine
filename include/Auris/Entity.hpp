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
    Entity* parent = nullptr;/*!< An Entity pointer: parent. An pointer to the parent entity. */
    Entity* child = nullptr;/*!< An Entity pointer: child. A pointer to the child entity. */
    Transform* transform; /*!< A Transform pointer: transform. An instance of the transform. */

    //! The engine contructor.
        /*!
         * Declares a new Transform.
        */
    Entity(){
        transform = new Transform(this);
    }

    //! The entity destructor.
        /*!
         * Deletes the Transform pointer.
        */
    ~Entity(){
        delete transform;
    }

    //! A setParent method.
        /*! sets the parent of the entity
        */
    void setParent(Entity* parent) {
        this->parent = parent;
        parent->setChild(this);
    }

    //! A setChild method.
        /*! sets the child of the entity
        */
    void setChild(Entity* child) {
        this->child = child;
        child->setParent(this);
    }


    //! The method updateTransform.
        /*!
         * Updates the enitities transform according to the physics body.
         * Should not be used by the game programmer.
         * Called every frame.
        */
    virtual void updateTransform(){}

    //! The scriptable function init.
        /*!
         * Used by the game programmer to add initial functionality to the entity.
         * Called upon initialization.
        */
    virtual void init() {}

    //! The scriptable function start.
        /*!
         * Used by the game programmer to add start functionality to the entity.
         * Called just before first update.
        */
    virtual void start() {}

    //! The scriptable function update, taking 1 argument.
        /*!
         * Used by the game programmer to add update functionality to the entity.
         * Called every frame.
          \param deltaTime a float value, that is the current delta time.
        */
    virtual void update(float deltaTime) {}

    //! The scriptable function onDestruction.
        /*!
         * Used by the game programmer to add on destruction functionality to the entity.
         * Called when the object is destroyed.
        */
    virtual void onDestruction() {}

};


}
