#include "Auris/Engine.hpp"
#include "Auris/Testing/DebugUI.hpp"

using namespace SRE;
using namespace glm;
using namespace std;
using namespace Auris;


Engine* Engine::instance;

Engine::Engine(int width, int height){
    if(instance != nullptr){
        std::cerr << "Multiple versions of Engine initialized. Only a single instance is supported." << std::endl; 
    }
    instance = this;

    Constants::width = width;
    Constants::height = height;
}

void Engine::startup(Game* game, int spritePoolCapacity){
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
        Constants::width,                               // width, in pixels
        Constants::height,                               // height, in pixels
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

    renderSystem.startup(spritePoolCapacity);


    world = new b2World(Convert::toB2(glm::vec2(0,0)));

    collisionHandler = new CollisionHandler;
    world->SetContactListener(collisionHandler);

    // Initialize Simple Render Engine

    auto sre = SimpleRenderEngine::instance;
    sre->getCamera()->setWindowCoordinates();

    Input::init(game);

    debugUI = new DebugUI();
    ImGui_SRE_Init(window);
    debugUI->startup(this);

    // INIT GAME
    game->init();

    run(window);

    shutdown();
}

void Engine::shutdown(){

    game->shutdown();

    game->entities.clear();
    game->destroyEntities.clear();
    game->newEntities.clear();

    Input::shutdown();

    delete world;
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
    float deltaTimeSec = 0;
    auto sre = SimpleRenderEngine::instance;

    while (Input::quit == 0){
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);
		
        if(debugUI->profiling) profile_Game_EarlyUpdateTimer.start();
        game->earlyUpdate(deltaTimeSec);
        if(debugUI->profiling) profile_Game_EarlyUpdateTimer.stop();

        sre->clearScreen(vec4(0,0,0,1));

        if(debugUI->profiling) profile_InputTimer.start();
        Input::update();
        if(debugUI->profiling) profile_InputTimer.stop();

        ImGui_SRE_NewFrame(window);
        debugUI->update(deltaTimeSec);
        
        //UPDATE
        if(!debugUI->pause || debugUI->runOneStep){

            // GAME UPDATE
            if(debugUI->profiling) profile_Game_UpdateTimer.start();
            game->update(deltaTimeSec);
            if(debugUI->profiling) profile_Game_UpdateTimer.stop();

            // entities UPDATE
            if(debugUI->profiling) profile_Entity_UpdateTimer.start();
            for(auto& el: game->newEntities)
                game->entities.push_back(el);
            game->newEntities.clear();
            for(auto& el: game->entities)
                el->update(deltaTimeSec);
            if(debugUI->profiling) profile_Entity_UpdateTimer.stop();

            if(debugUI->profiling) profile_PhysicsTimer.start();
            world->Step(deltaTimeSec, Constants::VELOCITY_ITERATIONS, Constants::POSITION_ITERATIONS);
            if(debugUI->profiling) profile_PhysicsTimer.stop();


            if(debugUI->profiling) profile_UpdatePhysicsEntityTransformTimer.start();
            for(auto& el: game->entities)
                el->updateTransform();
            if(debugUI->profiling) profile_UpdatePhysicsEntityTransformTimer.stop();
        }

        if(debugUI->profiling) profile_Game_LateUpdateTimer.start();
        game->lateUpdate(deltaTimeSec);
        if(debugUI->profiling) profile_Game_LateUpdateTimer.stop();

        if(debugUI->profiling) profile_RenderTimer.start();
        //DRAW
        renderSystem.update(deltaTimeSec);
        if(debugUI->profiling) profile_RenderTimer.stop();

        game->imGUI();

        debugUI->draw();
        ImGui::Render();


        if(debugUI->profiling) profile_SwapTimer.start();
        sre->swapWindow();
        if(debugUI->profiling) profile_SwapTimer.stop();

        std::sort(Game::instance->destroyEntities.begin(),Game::instance->destroyEntities.end());

        int index = 0;
        while (Game::instance->destroyEntities.size() > 0) {
            index = Game::instance->destroyEntities.back();
            Game::instance->entities.erase(Game::instance->entities.begin() + index);
            Game::instance->destroyEntities.pop_back();
        }
    }
}

