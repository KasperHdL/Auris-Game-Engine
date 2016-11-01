#pragma once

#include "../src/GameObjects/Components/Scriptable.hpp"

class CLASSNAME : public Scriptable {
public:

	void Init() {

	}

	void Update(float deltaTime) {

	}


	PlayerController(GameObject* gameObject) :Scriptable(gameObject) {};
};

