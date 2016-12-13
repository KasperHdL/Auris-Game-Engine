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

    virtual void UpdateTransform(){}

    // Scriptable functions

	virtual void Init() {} // Called upon initialization

	virtual void Start() {} // Called just before first update

	virtual void Update(float deltaTime) {} // Called every frame

	virtual void OnDestruction() {} // Called when object is destroyed

};


}
