#pragma once

#include "Auris/Entities/Nuggets/Transform.hpp"
#include "SRE/imgui_sre.hpp"
#include "SRE/Debug.hpp"
#include <string>
#include <vector>
#include "glm/glm.hpp"


namespace Auris{

//! The entity class
    /*! Have basic information about entities, every entity except the camera inherents from this class
    */
class Entity{
public:
    std::string type = "";/*!< A string value: type. The type of the entity. */
    std::string name = "";/*!< A string value: name. The name of the entity. */  
    Entity* parent = nullptr;/*!< An Entity pointer: parent. An pointer to the parent entity of this entity. */
    std::vector<Entity*> children;/*!< A vector of Entity pointer: childen. A pointer to the parent entity of this entity.*/
    Transform* transform; /*!< A Transform pointer: transform. An instance of the transform. */

    //! The entity contructor.
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

    //! Sets the parent of this entity.
        /*!
         * \param parent an Entity pointer, that is the parent to set.
         */
    void setParent(Entity* parent) {
        this->parent = parent;
    }

    //! Adds a child to this entity.
        /*!
         * \param child an Entity pointer, that is the child to add.
         */
    void addChild(Entity* child) {
        this->children.push_back(child);
    }

    //! Get the parent of this entity.
        /*!
         * \return parent, that is the parent of this entity.
         */
    Entity* getParent() {
        return parent;
    }

    //! Get a child of this entity by type.
        /*!
         * \param type a string value, that is the type of child.
         * \return Entity pointer, that is the first child of this entity that matches the string parameter.
         */
    Entity* getChildByType(std::string type){
        for (auto & child : children)
            if (child->type == type)
                return child;
        return nullptr;
    }

    //! Get a child of this entity by type.
        /*!
         * \param name a string value, that is the name of the child.
         * \return Entity pointer, that is the child of this entity that matches the string parameter.
         */
    Entity* getChildByName(std::string name) {
        for (auto & child : children)
            if (child->name == name)
                return child;
        return nullptr;
    }


    //! The scriptable function updateTransform.
        /*!
         * Updates the entities transform according to the physics body.
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

    //! The scriptable function debugDraw.
        /*!
         * Used by the game programmer to add debugdraw functionality to the entity.
         * Is called every frame, when the debug gui is open
        */
    virtual void debugDraw(){}

    //! The scriptable function inspectorImGui.
        /*!
         * Used by the game programmer to add inspector GUI functionality to the entity.
         * Is called every frame, when the inspector gui is open
         * The game programmer can call Entity::inspectorImGui to get Transform, Position, Scale and Rotation inspection
        */
    virtual void inspectorImGui(){
        if(ImGui::TreeNode("Transform")){
            ImGui::DragFloat3("Position", &transform->position.x);
            ImGui::DragFloat2("Scale", &transform->scale.x);
            ImGui::DragFloat("Rotation", &transform->rotation);
            ImGui::TreePop();
        } 
    }

};


}
