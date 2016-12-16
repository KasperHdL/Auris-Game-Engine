#pragma once

namespace Auris{
class Game;

//! The scene class
    /*! Used to create scenes in the game
    */
class Scene {
public:
    //! An init method, taking 1 argument.
        /*!
         * init in the scene is run when the game it initilized
         * The game programmer can use this to create new scenes in the game
         * \param game a Game Pointer. An instance of the game.
        */
    virtual void init() {}
};
}
