#include "Auris/Systems/Input.hpp"
#include <iostream>

using namespace Auris;

map<SDL_Scancode, bool> Input::heldKeys;
map<SDL_Scancode, bool> Input::downKeys;
map<SDL_Scancode, bool> Input::upKeys;

std::vector<SDL_GameController*> Input::ctrl;

int Input::quit = 0;

void Input::init(){
    SDL_Init(SDL_INIT_GAMECONTROLLER);
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            char *mapping;
            SDL_Log("Index \'%i\' is a compatible controller, named \'%s\'", i, SDL_GameControllerNameForIndex(i));
            ctrl.push_back(SDL_GameControllerOpen(i));
            mapping = SDL_GameControllerMapping(ctrl[i]);
            SDL_Log("Controller %i is mapped as \"%s\".", i, mapping);
            SDL_free(mapping);
        }
    }
}
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

            case SDL_CONTROLLERDEVICEADDED:
                controllerAdded(e);
            break;

            case SDL_QUIT:
            quit = 1;
            break;

            default:
            break;
        }
	}
}

void Input::shutdown(){

    heldKeys.clear();
    downKeys.clear();
    upKeys.clear();

    for(auto &c : ctrl){
        SDL_GameControllerClose(c);
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

void Input::controllerAdded(const SDL_Event &event){
    if (SDL_IsGameController(event.cdevice.which)) {
        char *mapping;
        SDL_Log("Index \'%i\' is a compatible controller, named \'%s\'", event.cdevice.which, SDL_GameControllerNameForIndex(event.cdevice.which));
        ctrl.push_back(SDL_GameControllerOpen(event.cdevice.which));
        mapping = SDL_GameControllerMapping(ctrl[event.cdevice.which]);
        SDL_Log("Controller %i is mapped as \"%s\".", event.cdevice.which, mapping);
        SDL_free(mapping);
    }
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
