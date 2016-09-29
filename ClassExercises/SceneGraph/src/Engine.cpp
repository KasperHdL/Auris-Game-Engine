#include "Engine.hpp"

#include <chrono>
#include <iostream>
#include <SDL_timer.h>
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>
#include "SRE/SimpleRenderEngine.hpp"
#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "SceneParser.hpp"

using namespace SRE;

void Engine::setup() {

    SimpleRenderEngine* sre = SimpleRenderEngine::instance;
    sre->getCamera()->lookAt({10,10,10}, {0,0,0}, {0,1,0});
    sre->getCamera()->setPerspectiveProjection(60,640,480,0.1,100);

    // setup test objec
    Mesh* sharedMesh = Mesh::createQuad();
    Shader* shader = Shader::getUnlit();

    auto testQuad = std::make_shared<GameObject>(sharedMesh, shader);
    testQuad->rotation = {-89,0,0};
    gameObjects.push_back(testQuad);
    
    std::vector<GameObjectDescriptor> scene = SceneParser::parseFile("data/car_house_tree.json");

    for(auto& g : scene){



    }
}

void Engine::start() {
    typedef std::chrono::high_resolution_clock Clock;
    auto t1 = Clock::now();
    int timePerFrameMillis = 1000/60;
    while (_gameRunning) {
        auto t2 = Clock::now();
        // time since last update
        float deltaTimeSec = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()/1000000.0f;
        update(deltaTimeSec);

        int updateTimeMillis = (int)std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t2).count();
        int wait = timePerFrameMillis - updateTimeMillis;
        if (wait > 0){
            SDL_Delay( wait );
        }
        t1 = t2;
    }
}

void Engine::update(float deltaTimeSec) {
    SimpleRenderEngine::instance->clearScreen({0,0,1,1});

    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        _gameRunning = false;
                    break;

                }
            break;

        }

    }


    // render game object
    for (auto & go : gameObjects){
        go->draw();
    }
    SimpleRenderEngine::instance->swapWindow();
}
