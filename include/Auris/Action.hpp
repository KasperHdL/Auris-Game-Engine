#pragma once
namespace Auris{
//! A namespace for scancodes
/*! If you need more actions it is possible to extend them yourself*/
namespace Action{
    const SDL_Scancode up = SDL_SCANCODE_UP;
    const SDL_Scancode down = SDL_SCANCODE_DOWN;
    const SDL_Scancode left = SDL_SCANCODE_LEFT;
    const SDL_Scancode right = SDL_SCANCODE_RIGHT;
    const SDL_Scancode quit = SDL_SCANCODE_ESCAPE;
    const SDL_Scancode debug = SDL_SCANCODE_F2;
    const SDL_Scancode pause = SDL_SCANCODE_F3;
    const SDL_Scancode stepOne = SDL_SCANCODE_F4;
    const SDL_Scancode playOnHold = SDL_SCANCODE_F5;
    const SDL_Scancode drawDebug = SDL_SCANCODE_F6;
}
}
