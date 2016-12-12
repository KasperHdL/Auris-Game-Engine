#include "Auris/Engine.hpp"
#include "DemoGame.hpp"
#include <SDL.h>

using namespace std;

DemoGame game;

int main(int argc, char** argv) {
    // Use windows coordinates in this example (lower left corner is (0,0), upper right corner is (width, height)
    float width = argv.length() > 0 ? argv[0][0] : 1920;
    float height = argv.length() > 0 ? argv[0][1] : 1080;

    Engine engine(width, height);
    engine.startup(&game);

    return 0;
}
