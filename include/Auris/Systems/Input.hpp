#pragma once

#include <SDL.h>
#include <map>
#include "SRE/imgui_sre.hpp"
#include <vector>

namespace Auris{
using namespace std;
class Input{
public:

    static void init();

	///A method to update the keypresses
	static void update();

    static void shutdown();
	
	///A method to get the key that is pressed down
	static bool keyDown(SDL_Scancode key);
	///A method to get the key that is lifted
	static bool keyUp(SDL_Scancode key);
	///A method to get the key that is currently being held down
	static bool keyHeld(SDL_Scancode key);

    static bool getCtrlButtonStatus();

    static int quit;
    static std::vector<SDL_GameController*> ctrl;

private:
	///A method to register a key being lifted up event
	static void keyUpEvent(const SDL_Event& event);
	///A method to register a key being pressed down event
	static void keyDownEvent(const SDL_Event& event);

	///A map to hold all keys that are currently being held
    static map<SDL_Scancode, bool> heldKeys;
	///A map to hold all keys that has been pressed down
    static map<SDL_Scancode, bool> downKeys;
	///A map tp hold all keys that has been lifted up
    static map<SDL_Scancode, bool> upKeys;

    static void controllerAdded(const SDL_Event& event);

};

class Button{
public:
    SDL_Scancode up = SDL_SCANCODE_UP;
    SDL_Scancode down = SDL_SCANCODE_DOWN;
    SDL_Scancode left = SDL_SCANCODE_LEFT;
    SDL_Scancode right = SDL_SCANCODE_RIGHT;
    SDL_Scancode quit = SDL_SCANCODE_ESCAPE;
};

class Keys {
public:
    Keys();
    ~Keys();
    void setKey(string key, SDL_Scancode mappedkey); ///A method to map a string to a SDL key
    SDL_Scancode getKey(string key);///A method to get the SDL key based on the string input
private:

    map<string, SDL_Scancode> allKeys; ///A map to hold all the SDL keys, and the strings that correspond to that key
};
}
