#include "Input.hpp"

///This method clears all the keys that are currently stored, and then updates them to what ever keys are being manipulated this frame
void Input::update() {
	downKeys.clear();//clear down keys
	upKeys.clear();//clear up keys
	SDL_Event e; ///An SDL event to figure out which keys are being manipulated
	if (SDL_PollEvent(&e)) { //If there is an event
		if (e.type == SDL_KEYDOWN) { //if this event is that a key is being pressed down
			if (e.key.repeat == 0) { //if this key is not being held down
				keyDownEvent(e); //register the event
			}
		}
		else if (e.type == SDL_KEYUP) { //if this event is that a key is being lifted up
			keyUpEvent(e); //register the event
		}
	}
}

///This method registers a keydown event, and therefore takes an SDL event as input, to figure out which key has been pressed
void Input::keyDownEvent(const SDL_Event& event) {
	downKeys[event.key.keysym.scancode] = true; //Save the key in down keys
	heldKeys[event.key.keysym.scancode] = true; //Save the key in held keys
}

///This method registers a keyup event, and therefore takes and SDL event as input, to figure out which key has been released
void Input::keyUpEvent(const SDL_Event& event) {
	upKeys[event.key.keysym.scancode] = true; //Save the key in up keys
	heldKeys[event.key.keysym.scancode] = false; //Remove the key from held keys
}

///This method returns true if the key being checked is currently being pressed down, otherwise false
bool Input::keyDown(SDL_Scancode key) {
	return downKeys[key];
}
///This method return true if the key being checked is currently being lifted up, otherwise false
bool Input::keyUp(SDL_Scancode key) {
	return upKeys[key];
}
///This method returns true if the key being checked is currently being held down, otherwise false
bool Input::keyHeld(SDL_Scancode key) {
	return heldKeys[key];
}
