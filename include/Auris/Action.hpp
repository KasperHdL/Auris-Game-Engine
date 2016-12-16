#pragma once
#include "SDL.h"
namespace Auris{
//! A namespace for scancodes
/*! If you need more actions it is possible to extend them yourself*/
namespace Action{
    const SDL_Scancode up              = SDL_SCANCODE_UP;
    const SDL_Scancode down            = SDL_SCANCODE_DOWN;
    const SDL_Scancode left            = SDL_SCANCODE_LEFT;
    const SDL_Scancode right           = SDL_SCANCODE_RIGHT;
    const SDL_Scancode quit            = SDL_SCANCODE_ESCAPE;

    const SDL_Scancode debug_menu      = SDL_SCANCODE_F2;
    const SDL_Scancode toggleInspector = SDL_SCANCODE_F3;
    const SDL_Scancode toggleHierarchy = SDL_SCANCODE_F4;
    const SDL_Scancode toggleProfiler  = SDL_SCANCODE_F5;

    const SDL_Scancode drawColliders   = SDL_SCANCODE_F7;
    const SDL_Scancode drawDebug       = SDL_SCANCODE_F8;

    const SDL_Scancode pause           = SDL_SCANCODE_F10;
    const SDL_Scancode stepOne         = SDL_SCANCODE_F11;
    const SDL_Scancode playOnHold      = SDL_SCANCODE_F12;

    const SDL_Scancode w               = SDL_SCANCODE_W;
    const SDL_Scancode a               = SDL_SCANCODE_A;
    const SDL_Scancode s               = SDL_SCANCODE_S;
    const SDL_Scancode d               = SDL_SCANCODE_D;
    const SDL_Scancode enter           = SDL_SCANCODE_RETURN;
    const SDL_Scancode space           = SDL_SCANCODE_SPACE;
    const SDL_Scancode z = SDL_SCANCODE_Z;
}
}
