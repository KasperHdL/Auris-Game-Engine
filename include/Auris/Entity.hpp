#pragma once

#include "Auris/Entities/Nuggets/Transform.hpp"
#include <string>


namespace Auris{

class Entity{
public:
    std::string name = "";
    Entity* parent = nullptr;
    Transform* transform;

    Entity(){
        transform = new Transform(this);
    }

    ~Entity(){
        delete transform;
    }

    //! Used by PhysicsEntities
    virtual void updateTransform(){}

    //! Scriptable functions
    virtual void init() {} // Called upon initialization

    virtual void start() {} // Called just before first update

    virtual void update(float deltaTime) {} // Called every frame

    virtual void onDestruction() {} // Called when object is destroyed

};


}
