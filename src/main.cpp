#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SRE/SimpleRenderEngine.hpp"
#include "Engine.hpp"
#include "Utility/Pool.hpp"

#include "GameObjects/Components/Sprite.hpp"

using namespace std;

int main(int argc, char** argv) {
    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    int width = 640;
    int height = 480;

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            width,                               // width, in pixels
            height,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
    );
    SDL_SetWindowTitle(window,"Gold Engine");
    // Check that the window was successfully made
    if (window == NULL) {
        // In the event that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SRE::SimpleRenderEngine r{window};

    // Use windows coordinates in this example (lower left corner is (0,0), upper right corner is (width, height)
    
    float deltaTimeSec;
    Uint64 END = SDL_GetPerformanceCounter();
    Uint64 START = SDL_GetPerformanceCounter();
    Pool<Sprite> sprites = Pool<Sprite>(128);
    Pool<glm::vec2> positions = Pool<glm::vec2>(128);
    END = SDL_GetPerformanceCounter();

    deltaTimeSec = clamp(((END - START) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);

    cout << "construction took " << deltaTimeSec<< endl;
    r.getCamera()->setWindowCoordinates();

    START = SDL_GetPerformanceCounter();
    for(int i = 0;i< sprites.capacity;i++){
        Sprite* s = sprites.create();
        glm::vec2* p = positions.create();

        s->mesh = Mesh::createCube();
        s->color = vec4(1,0,1,1);
        s->scale = glm::vec2(10,10);

        *p = glm::vec2(i*10,i * 10);

    }

    END = SDL_GetPerformanceCounter();
    deltaTimeSec = clamp(((END - START) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);

    cout << "values initialized " << deltaTimeSec << endl;

    
    START = SDL_GetPerformanceCounter();
        r.clearScreen(vec4(0.3f,0.3f,0.3f,1));
    for(int i = 0;i< sprites.capacity;i++){
        Shader* shader = Shader::getUnlitSprite();
        shader->setVector("color", sprites[i]->color);
        SimpleRenderEngine::instance->draw(sprites[i]->mesh, glm::translate(glm::mat4(1), vec3(*positions[i], 0)), shader);
    
    }

    END = SDL_GetPerformanceCounter();
    deltaTimeSec = clamp(((END - START) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);
    cout << "values drawn " << deltaTimeSec << endl;
    r.swapWindow();
    SDL_Delay(2000); 
    cout << "read" << endl;


    Engine engine(width, height);
    engine.startup();
    engine.run();
    engine.shutdown();
    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();

    return 0;
}
