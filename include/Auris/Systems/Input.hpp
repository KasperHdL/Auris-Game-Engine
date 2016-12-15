#pragma once

#include <SDL.h>
#include <map>
#include "SRE/imgui_sre.hpp"
#include <vector>
#include "glm/glm.hpp"

namespace Auris{
class Game;

//! The Input class
    /*! Handles all input of the engine
     * Everything in the input class is static
    */
class Input{
public:

    //! A static init method, taking 1 argument.
        /*!
         * Initializes the input system, meaning initilizing controllers
         * \param game a Game pointer, that is an instance of the game.
        */
    static void init(Game* game);

    //! A static update method.
        /*!
         * Update all key presses, and controller connected/disconnected events
        */
	static void update();

    //! A static shutdown method.
        /*!
         * Shutdown the input system, meaning clears all key presses
        */
    static void shutdown();

    //! A static keyDown method, taking 1 argument.
        /*!
         * a method to get the key that is pressed down
         * \param key a SDL_Scancode, that is the scancode of the keyboard key
         * \return bool, the state of the key
        */
    static bool keyDown(SDL_Scancode key);

    //! A static keyUp method, taking 1 argument.
        /*!
         * a method to get the key that is lifted
         * \param key a SDL_Scancode, that is the scancode of the keyboard key
         * \return bool, the state of the key
        */
	static bool keyUp(SDL_Scancode key);

    //! A static keyHeld method, taking 1 argument.
        /*!
         * a method to get the key that is currently being held down
         * \param key a SDL_Scancode, that is the scancode of the keyboard key
         * \return bool, the state of the key
        */
	static bool keyHeld(SDL_Scancode key);

    static int quit; /*!< A static int value: quit. Used to figure out if the game is quitted. */

    //! A static getControllerButtonState method, taking 2 arguments.
        /*!
         * a method to get the state of the button on a controller.
         * \param controllerID an int, that is the id of the controller
         * \param button a SDL_GameControllerButton, that is the button to get the state of
         * \return bool, the state of the button (true for pressed down)
        */
    static int getControllerButtonState(int controllerID, SDL_GameControllerButton button);

    //! A static getControllerAxisState method, taking 2 arguments.
        /*!
         * a method to get the state of the axis on a controller.
         * \param controllerID an int, that is the id of the controller
         * \param axis a SDL_GameControllerAxis, that is the axis to get the state of
         * \return int, the state of the Axis (ranging from -32768 to 32767, trigger from 0 to 32767)
        */
    static int getControllerAxisState(int controllerID, SDL_GameControllerAxis axis);

    //! A static getControllerLeftStickState method, taking 1 argument.
        /*!
         * a method to get the state of the left stick on a controller.
         * \param controllerID an int, that is the id of the controller
         * \return vec2, the state of both axis of the left stick the Axis (ranging from -32768 to 32767)
        */
    static glm::vec2 getControllerLeftStickState(int controllerID);

    //! A static getControllerRightStickState method, taking 1 argument.
        /*!
         * a method to get the state of the right stick on a controller.
         * \param controllerID an int, that is the id of the controller
         * \return vec2, the state of both axis of the right stick the Axis (ranging from -32768 to 32767)
        */
    static glm::vec2 getControllerRightStickState(int controllerID);


private:

    //! A static keyUpEvent method, taking 1 argument.
        /*!
         * A method to register a key being lifted up event.
         * \param &event an const SDL_Event, that is the specific event
        */
	static void keyUpEvent(const SDL_Event& event);

    //! A static keyUpEvent method, taking 1 argument.
        /*!
         * A method to register a key being pressed down event.
         * \param &event an const SDL_Event, that is the specific event
        */
	static void keyDownEvent(const SDL_Event& event);

    static std::map<SDL_Scancode, bool> heldKeys; /*!< A static map of SDL_Scancode and bool: heldKeys. Holds the state of the keys currently being held */

    static std::map<SDL_Scancode, bool> downKeys; /*!< A static map of SDL_Scancode and bool: downKeys. Holds the state of the keys that has been pressed down */

    static std::map<SDL_Scancode, bool> upKeys; /*!< A static map of SDL_Scancode and bool: upKeys. Holds the state of the keys currently that has been lifted up */

    //! A static controllerAdded method, taking 1 argument.
        /*!
         * A method to register a controller being added event.
         * \param &event an const SDL_Event, that is the specific event
        */
    static void controllerAdded(const SDL_Event& event);

    //! A static initController method, taking 1 argument.
        /*!
         * A method to register a controller being initialized with a button press event.
         * \param &event an const SDL_Event, that is the specific event
        */
    static void initController(const SDL_Event& event);

    //! A static controllerRemoved method, taking 1 argument.
        /*!
         * A method to register a controller being disconnected event.
         * \param &event an const SDL_Event, that is the specific event
        */
    static void controllerRemoved(const SDL_Event& event);

    static std::map<SDL_JoystickID,SDL_GameController*> ctrl; /*!< A static map of SDL_JoystickID and SDL_GameController pointer: ctrl. Holds the id and their controllers */

    static Game* game; /*!< A static Game pointer: game. Holds an instance of the game */

};
}
