#include "Auris/Systems/Input.hpp"
#include <iostream>
#include "Auris/Game.hpp"

using namespace Auris;

std::map<SDL_Scancode, bool> Input::heldKeys;
std::map<SDL_Scancode, bool> Input::downKeys;
std::map<SDL_Scancode, bool> Input::upKeys;

std::map<SDL_JoystickID,SDL_GameController*> Input::ctrl;

int Input::quit = 0;
Game* Input::game;

void Input::init(Game* game){
    Input::game = game;

    if(SDL_Init(SDL_INIT_GAMECONTROLLER)<0){
         fprintf(stderr, "Couldn't initialize controller: %s\n", SDL_GetError());
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

            case SDL_CONTROLLERBUTTONDOWN:
                initController(e);
            break;

            case SDL_CONTROLLERDEVICEREMOVED:
                controllerRemoved(e);
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

//    for(auto &c : ctrl){
//        SDL_GameControllerClose(c);
//    }
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
            //char *mapping;
            //SDL_Log("Index \'%i\' is a compatible controller, named \'%s\'", event.cdevice.which, SDL_GameControllerNameForIndex(event.cdevice.which));
            SDL_GameController* temp = SDL_GameControllerOpen(event.cdevice.which);
            //mapping = SDL_GameControllerMapping(temp);
            //SDL_Log("Controller %i is mapped as \"%s\".", event.cdevice.which, mapping);
            //SDL_free(mapping);
            game->controllerConnected();
    }
}

void Input::initController(const SDL_Event& event){
    //std::cout << "Controller: " <<event.cbutton.which << " Button: "<< (int)event.cbutton.button << std::endl;
    if (SDL_IsGameController(event.cbutton.which)) {
        if(!ctrl.count(event.cbutton.which)){
            ctrl[event.cbutton.which]= SDL_GameControllerOpen(event.cdevice.which);
            game->controllerActivated(event.cbutton.which);
        }
    }
}

void Input::controllerRemoved(const SDL_Event& event){
    if (SDL_IsGameController(event.cdevice.which)) {
            SDL_GameControllerClose(ctrl[event.cdevice.which]);
            std::map<SDL_JoystickID,SDL_GameController*>::iterator it;
            it=ctrl.find(event.cdevice.which);
            ctrl.erase (it);
            game->controllerDisconnected(event.cdevice.which);
        }
}

glm::vec2 Input::getControllerLeftStickState(int controllerID){
    return glm::vec2(SDL_GameControllerGetAxis(ctrl[controllerID],SDL_CONTROLLER_AXIS_LEFTX),SDL_GameControllerGetAxis(ctrl[controllerID],SDL_CONTROLLER_AXIS_LEFTY));
}

glm::vec2 Input::getControllerRightStickState(int controllerID){
    return glm::vec2(SDL_GameControllerGetAxis(ctrl[controllerID],SDL_CONTROLLER_AXIS_RIGHTX),SDL_GameControllerGetAxis(ctrl[controllerID],SDL_CONTROLLER_AXIS_RIGHTY));
}

bool Input::getControllerButtonState(int controllerID, SDL_GameControllerButton button){
    //std::cout << "controllerID: " << controllerID <<" Button: "<< button << " State: " << (bool)SDL_GameControllerGetButton(ctrl[controllerID],button) <<std::endl;
    return (SDL_GameControllerGetButton(ctrl[controllerID],button) == 1);
}

int Input::getControllerAxisState(int controllerID, SDL_GameControllerAxis axis){
    //std::cout << ctrl.size() << std::endl;
    return SDL_GameControllerGetAxis(ctrl[controllerID],axis);
}
