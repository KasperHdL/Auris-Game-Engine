#include "Auris/Engine.hpp"
#include "SpriteDemo.hpp"
#include <SDL.h>

using namespace std;

SpriteDemo game;

int main(int argc, char** argv) {
    // Use windows coordinates in this example (lower left corner is (0,0), upper right corner is (width, height)
    float width = 1280;
    float height = 720;

    Auris::Engine engine(width, height);
    engine.startup(&game, 4096);

    return 0;
}
