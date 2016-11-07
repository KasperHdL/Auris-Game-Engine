#pragma once

#include <SDL.h>
#include <map>

using namespace std;
class Input{
public:
	///A method to update the keypresses
	static void update();
	
	///A method to get the key that is pressed down
	static bool keyDown(SDL_Scancode key);
	///A method to get the key that is lifted
	static bool keyUp(SDL_Scancode key);
	///A method to get the key that is currently being held down
	static bool keyHeld(SDL_Scancode key);
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
};
