#include "Auris/Engine.hpp"
#include "Auris/Testing/DebugUI.hpp"
#include "Auris/Systems/AssetSystem.hpp"

using namespace SRE;
using namespace glm;
using namespace std;
using namespace Auris;


b2World* Engine::world;

void Engine::startup(Game* game){
    this->game = game;

    if (SDL_Init(SDL_INIT_VIDEO) == -1) // Initialize SDL2
        cout << SDL_GetError() << endl;

    if (SDL_Init(SDL_INIT_AUDIO) == -1) // Initialize SDL2_audio
        cout << SDL_GetError() << endl;

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024 ) == -1 ) // Initialize SDL_mixer
        cout << SDL_GetError() << endl;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create an application window with the following settings:

    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        width,                               // width, in pixels
        height,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    SDL_SetWindowTitle(window,"[Au]ris Engine");
    // Check that the window was successfully made

    if (window == NULL) {
        // In the event that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        exit(1);
    }

    SRE::SimpleRenderEngine r{window};

    renderSystem.startup(64);


    world = new b2World(Convert::toB2(glm::vec2(0,0)));

    collisionHandler = new CollisionHandler;
    Engine::world->SetContactListener(collisionHandler);

    // Initialize Simple Render Engine

    //nisse->setRotation(-3.14);
    //nisse->moveCamera(vec2(400,0));
    //nisse->moveCamera(vec2(400,0));
    auto sre = SimpleRenderEngine::instance;
    sre->getCamera()->setWindowCoordinates();

    Input::init(game);

    debugUI = new DebugUI();
    debugUI->startup(this);

    // INIT GAME
    game->init();

    run(window);

    shutdown();
}

void Engine::shutdown(){
    game->shutdown();
    Input::shutdown();

    delete Engine::world;
    Engine::world = nullptr;
    //delete collisionHandler;

    renderSystem.shutdown();

    debugUI->shutdown();

    //! Close SDL_mixer
    Mix_CloseAudio();

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
}


void Engine::run(SDL_Window* window){
    // delta time from http://gamedev.stackexchange.com/a/110831
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    quit = 0;
    float deltaTimeSec = 0;
    auto sre = SimpleRenderEngine::instance;

	//Initialize MemoryLeakDetector
	memLeakDet = MemoryLeakDetector();

    //DEBUG INFORMATION TODO should be ignored on release build
   
    int arrIndex = 0;
    const int arrSize = 600;
    float arr_deltaTime[arrSize] = {};
    float max_deltaTime = 0;

    
    float arr_virtMem[arrSize] = {};
    float max_virtMem = 0;

    float arr_physMem[arrSize] = {};
    float max_physMem = 0;

    int max_renderSprites = 0;

    bool toggle_goInspector = false;
    bool toggle_showcasePanel = false;
    bool toggle_cameraControls = false;

    while (Input::quit == 0){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);
		
        game->earlyUpdate(deltaTimeSec);

        sre->clearScreen(vec4(0,0,0,1));

        //nisse->rotateCamera(0.1f);

        Input::update();

        debugUI->update(deltaTimeSec);
        
        //UPDATE
        if(!debugUI->pause || debugUI->runOneStep){

            // GAME UPDATE
            game->update(deltaTimeSec);

            // entities UPDATE
            for(auto& el: game->entities)
                el->update(deltaTimeSec);

            Engine::world->Step(deltaTimeSec, VELOCITY_ITERATIONS, POSITION_ITERATIONS);


            for(auto& el: game->entities)
                el->updateTransform();
        }

        game->lateUpdate(deltaTimeSec);

        //DRAW
        renderSystem.update(deltaTimeSec);

        debugUI->draw();


        sre->swapWindow();
    }
}

