#include <SDL.h>

using namespace std;

int main(int argc, char** argv) {
    // Use windows coordinates in this example (lower left corner is (0,0), upper right corner is (width, height)
    
    GoldEngine engine(width, height);
    engine.startup(window);
    engine.run(window);
    engine.shutdown();
    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    return 0;
}
