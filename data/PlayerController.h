#pragma once

#include "../src/GameObjects/Components/Scriptable.hpp"

class PlayerController : Scriptable {
public:

private:

	void Init() override {
		
	}

	void Update(float deltaTime) override {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_a)
				{
					parent->body->ApplyForceToCenter(b2Vec2(-10, 0), true);
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					parent->body->ApplyForceToCenter(b2Vec2(10, 0), true);
				}
				if (event.key.keysym.sym == SDLK_w)
				{
					parent->body->ApplyForceToCenter(b2Vec2(0, 10), true);
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					parent->body->ApplyForceToCenter(b2Vec2(0, -10), true);
				}
				break;
				/* SDL_QUIT event (window close) */
			default:
				break;
			}

		}
	}
};


