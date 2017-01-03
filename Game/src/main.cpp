#include "Auris/Auris.hpp"
#include "DemoGame.hpp"
#include <SDL.h>

using namespace std;

DemoGame game = DemoGame();

int main(int argc, char** argv) {
    // Use windows coordinates in this example (lower left corner is (0,0), upper right corner is (width, height)
    float width = 1280;
    float height = 720;

    if (argc > 1) {
        if ((string)argv[1] == "1.5") {
            width *= 1.5f;
            height *= 1.5f;
        }

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
