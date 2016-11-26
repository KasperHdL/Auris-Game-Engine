#include "Auris/Engine.hpp"
#include "DemoGame.hpp"
#include <SDL.h>

using namespace std;

DemoGame game;

int main(int argc, char** argv) {
    // Use windows coordinates in this example (lower left corner is (0,0), upper right corner is (width, height)
    
    Engine engine(1280, 720);
    engine.startup(&game);

    return 0;
}
