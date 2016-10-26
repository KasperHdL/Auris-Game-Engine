#pragma once

#include "Component.hpp"
#include <string>
#include <iostream>
#include "SDL.h"

class Scriptable : public Component {
	public:
		GameObject* parent = nullptr;

		virtual void Init() {}; // Called upon initialization

		virtual void Start() {}; // Called just before first update

		virtual void Update(float deltaTime) {}; // Called every frame

		virtual void OnDestruction() {}; // Called when object is destroyed

		virtual void OnCollisionEnter() {}; // Called upon collision with another game object

		virtual void OnCollisionStay() {}; // Called while colliding with another game object

		virtual void OnCollisionExit() {}; // Called when exiting collision with another game object

		Scriptable(GameObject* gameObject) :Component(gameObject) {};
};

