#include "Auris/Engine.hpp"

#ifdef DEBUG
#include "Auris/Testing/DebugUI.hpp"
#endif

#include "Auris/Systems/CollisionHandler.hpp"


namespace Auris{
using namespace SRE;
using namespace glm;
using namespace std;


Engine* Engine::instance;

Engine::Engine(int width, int height){
    if(instance != nullptr){
        std::cerr << "Multiple versions of Engine initialized. Only a single instance is supported." << std::endl; 
    }
    instance = this;

    Constants::width = width;
    Constants::height = height;

#ifdef DEBUG
    std::cout << "--[Debug mode active]--" << std::endl;
#endif

}

void Engine::startup(Game* game){
    this->game = game;

    if (SDL_Init(SDL_INIT_VIDEO) == -1) // Initialize SDL2
        cout << SDL_GetError() << endl;

    if (SDL_Init(SDL_INIT_AUDIO) == -1) // Initialize SDL2_audio
        cout << SDL_GetError() << endl;

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024 ) == -1 ) // Initialize SDL_mixer
        cout << SDL_GetError() << endl;

    //sets the sdl attributes
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

    renderSystem.startup();

    //Makes new physics world
    world = new b2World(Convert::toB2(glm::vec2(0,0)));

    collisionHandler = new CollisionHandler;
    world->SetContactListener(collisionHandler);

    // Initialize Simple Render Engine

    auto sre = SimpleRenderEngine::instance;
    sre->getCamera()->setWindowCoordinates();

    Input::init(game);

    //starts imgui
    ImGui_SRE_Init(window);

#ifdef DEBUG
    debugUI = new DebugUI();
    debugUI->startup(this);
#endif

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

#ifdef DEBUG
    debugUI->shutdown();
#endif

    // Close SDL_mixer
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
    auto sre = SimpleRenderEngine::instance;

    while (Input::quit == 0){ //as long as there is no SDL quit event
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        float deltaTimeSec = clamp(((NOW - LAST) / (float)SDL_GetPerformanceFrequency() ),0.0f,1.0f);
		
#ifdef DEBUG
        if(!debugUI->pause || debugUI->runOneStep){
            if(debugUI->profiling) profile_Game_EarlyUpdateTimer.start();
#endif

            deltaTime = deltaTimeSec;
            time += deltaTimeSec;
        //GAME EARLY UPDATE!
            game->earlyUpdate(deltaTimeSec);

#ifdef DEBUG
            if(debugUI->profiling) profile_Game_EarlyUpdateTimer.stop();
        }
#endif

        sre->clearScreen(backgroundColor); //background color

#ifdef DEBUG
        if(debugUI->profiling) profile_InputTimer.start();
#endif

        //INPUT UPDATE
        Input::update();
        
#ifdef DEBUG
        if(debugUI->profiling) profile_InputTimer.stop();
#endif

        ImGui_SRE_NewFrame(window);

#ifdef DEBUG
        debugUI->update(deltaTimeSec);
        if(!debugUI->pause || debugUI->runOneStep){
            if(debugUI->profiling) profile_Game_UpdateTimer.start();
#endif

        //UPDATE
            // GAME UPDATE
            game->update(deltaTimeSec);

#ifdef DEBUG
            if(debugUI->profiling) profile_Game_UpdateTimer.stop();
            if(debugUI->profiling) profile_Entity_UpdateTimer.start();
#endif

            // ENTITIES UPDATE
            for(auto& el: game->newEntities)
                game->entities.push_back(el);
            game->newEntities.clear();
            for(auto& el: game->entities)
                el->update(deltaTimeSec);

#ifdef DEBUG
            if(debugUI->profiling) profile_Entity_UpdateTimer.stop();
            if(debugUI->profiling) profile_PhysicsTimer.start();
#endif

            //PHYSICS STEPS
            world->Step(deltaTimeSec, Constants::VELOCITY_ITERATIONS, Constants::POSITION_ITERATIONS);

#ifdef DEBUG
            if(debugUI->profiling) profile_PhysicsTimer.stop();
            if(debugUI->profiling) profile_UpdatePhysicsEntityTransformTimer.start();
#endif

            //TRANSFORM UPDATE
            for(auto& el: game->entities)
                el->updateTransform();

#ifdef DEBUG
            if(debugUI->profiling) profile_UpdatePhysicsEntityTransformTimer.stop();
            if(debugUI->profiling) profile_Game_LateUpdateTimer.start();
#endif

            //GAME LATE UPDATE
            game->lateUpdate(deltaTimeSec);

#ifdef DEBUG
            if(debugUI->profiling) profile_Game_LateUpdateTimer.stop();
        }
        if(debugUI->profiling) profile_RenderTimer.start();
#endif
        
        //DRAW
        renderSystem.update(deltaTimeSec);

#ifdef DEBUG
        if(debugUI->profiling) profile_RenderTimer.stop();
#endif

        game->imGui();

#ifdef DEBUG
        debugUI->draw();
#endif

        ImGui::Render();


#ifdef DEBUG
        if(debugUI->profiling) profile_SwapTimer.start();
#endif

        sre->swapWindow();

#ifdef DEBUG
        if(debugUI->profiling) profile_SwapTimer.stop();
#endif

        std::sort(Game::instance->destroyEntities.begin(),Game::instance->destroyEntities.end());

        int index = 0;
        while (Game::instance->destroyEntities.size() > 0) {
            index = Game::instance->destroyEntities.back();
            Game::instance->entities.erase(Game::instance->entities.begin() + index);
            Game::instance->destroyEntities.pop_back();
        }
    }


}

void Engine::setAmbientLight(vec3 color){
    SRE::SimpleRenderEngine::instance->setAmbientLight(color);
}

void Engine::setBackgroundColor(vec4 color){
    backgroundColor = color;
}
}
