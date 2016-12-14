#include "Auris/Engine.hpp"
#include "ParticleDemo.hpp"
#include <SDL.h>

using namespace std;

ParticleDemo game;

int main(int argc, char** argv) {
    // Use windows coordinates in this example (lower left corner is (0,0), upper right corner is (width, height)
    SDL_DisplayMode* mode;
    Uint32 f = mode->format;

    float screenWidth = mode->w;
    float screenHeight = mode->h;

    float width = 1280;
    float height = 720;

    Engine engine(width, height);
    engine.startup(&game);

    return 0;
}
