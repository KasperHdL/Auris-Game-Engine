#include "Input.hpp"
#include <iostream>

map<SDL_Scancode, bool> Input::heldKeys;
map<SDL_Scancode, bool> Input::downKeys;
map<SDL_Scancode, bool> Input::upKeys;

map <SDL_GameControllerButton, bool> joyHeldKeys;
map <SDL_GameControllerButton, bool> joyDownKeys;
map <SDL_GameControllerButton, bool> joyUpKeys;

int Input::quit = 0;

///This method clears all the keys that are currently stored, and then updates them to what ever keys are being manipulated this frame
void Input::update() {
	downKeys.clear();//clear down keys
	upKeys.clear();//clear up keys
	SDL_Event e; ///An SDL event to figure out which keys are being manipulated
    while (SDL_PollEvent(&e)) { //If there is an event
        ImGui_SRE_ProcessEvent(&e);
        switch (e.type){

            case SDL_KEYDOWN:
            if (e.key.repeat == 0) { //if this key is not being held down
                keyDownEvent(e); //register the event
            }
            break;

            case SDL_KEYUP:
                keyUpEvent(e); //register the event
            break;

            case SDL_JOYBUTTONDOWN:
                   //joyKeyDownEvent(e);
            break;

            case SDL_JOYBUTTONUP:
                //joyKeyUpEvent(e);
            break;

        case SDL_QUIT:
            quit = 1;
            default:
            break;
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
    heldKeys[event.key.keysym.scancode] = false; //Remove the key from held keys
	upKeys[event.key.keysym.scancode] = true; //Save the key in up keys
}

//void Input::joyKeyDownEvent(const SDL_Event& event){
//    joyDownKeys[event.jbutton.button] = true;
//    joyHeldKeys[event.jbutton.button] = true;
//}

//void Input::joyKeyUpEvent(const SDL_Event& event){
//    joyHeldKeys[event.jbutton.button] =false;
//    joyUpKeys[event.jbutton.button] = true;
//}

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




// KEYS CLASS
Keys::Keys() {
    allKeys["up"] = SDL_SCANCODE_UP;
    allKeys["down"] = SDL_SCANCODE_DOWN;
    allKeys["left"] = SDL_SCANCODE_LEFT;
    allKeys["right"] = SDL_SCANCODE_RIGHT;
    allKeys["quit"] = SDL_SCANCODE_ESCAPE;
}
Keys::~Keys() {
    allKeys.clear();
}
///maps the string to a SDL scancode
void Keys::setKey(string key, SDL_Scancode mappedkey) {
    allKeys[key] = mappedkey;///save the SDL key in the map all keys
}

///returns the SDL key corresponding to the string that has been set in the allKeys map (If it has not been set, it will return null)
SDL_Scancode Keys::getKey(string key) {
    return allKeys[key]; ///returns the SDL key with the string mapped
}
