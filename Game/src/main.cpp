#include "Auris/Engine.hpp"
#include "DemoGame.hpp"
#include <SDL.h>

using namespace std;

DemoGame game;

int main(int argc, char** argv) {
    // Use windows coordinates in this example (lower left corner is (0,0), upper right corner is (width, height)
    float width = 1280;
    float height = 720;

    if (argc > 1) {
        if ((string)argv[1] == "2") {
            width *= 2;
            height *= 2;
        }

        if ((string)argv[1] == "3") {
            width *= 3;
            height *= 3;
        }
    }

    Engine engine(width, height);
    engine.startup(&game);

    return 0;
}
