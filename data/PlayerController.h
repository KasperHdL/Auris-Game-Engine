#pragma once

#include "../src/GameObjects/Components/Scriptable.hpp"

class PlayerController : public Scriptable {
public:
	int force;
	void Init() {
		force = 1000;
	}

	void Update(float deltaTime) {
		//TODO apply force according to keyboard input
		gameObject->body->ApplyForceToCenter(b2Vec2(force, 0), true);
		gameObject->body->ApplyForceToCenter(b2Vec2(0, force), true);
	}


	PlayerController(GameObject* gameObject) :Scriptable(gameObject) {};
};


