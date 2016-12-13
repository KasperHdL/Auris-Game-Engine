#pragma once

#include <SDL.h>
#include <map>
#include "SRE/imgui_sre.hpp"
#include <vector>

namespace Auris{
class Game;
class Input{
public:

    static void init(Game* game);

	///A method to update the keypresses
	static void update();

    static void shutdown();
	
	///A method to get the key that is pressed down
	static bool keyDown(SDL_Scancode key);
	///A method to get the key that is lifted
	static bool keyUp(SDL_Scancode key);
	///A method to get the key that is currently being held down
	static bool keyHeld(SDL_Scancode key);

    static int quit;

    static int getControllerButtonState(int controllerID, SDL_GameControllerButton button);


private:
	///A method to register a key being lifted up event
	static void keyUpEvent(const SDL_Event& event);
	///A method to register a key being pressed down event
	static void keyDownEvent(const SDL_Event& event);

	///A map to hold all keys that are currently being held
    static std::map<SDL_Scancode, bool> heldKeys;
	///A map to hold all keys that has been pressed down
    static std::map<SDL_Scancode, bool> downKeys;
	///A map tp hold all keys that has been lifted up
    static std::map<SDL_Scancode, bool> upKeys;

    static void controllerAdded(const SDL_Event& event);

    static void initController(const SDL_Event& event);

    static void controllerRemoved(const SDL_Event& event);

    static std::map<SDL_JoystickID,SDL_GameController*> ctrl;

    static Game* game;

};
}
