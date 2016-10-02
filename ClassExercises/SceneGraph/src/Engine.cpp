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
    sre->getCamera()->setPerspectiveProjection(60,640,480,0.1,100);
    cameraPosition = glm::vec3(10,10,10);
    cameraSpeed = 1;

    // setup test objec
    Mesh* plane = Mesh::createQuad();
    Mesh* cube  = Mesh::createCube();
    Mesh* sphere = Mesh::createSphere();

    Shader* shader = Shader::getUnlit();

    std::vector<GameObjectDescriptor> scene = SceneParser::parseFile("data/car_house_tree.json");

    for(auto& g : scene){
        std::string meshName = g.meshName;
        Mesh* mesh;

        if(meshName == "plane")
            mesh = plane;
        else if(meshName == "cube")
            mesh = cube;
        else if(meshName == "sphere")
            mesh = sphere;

        auto go = std::make_shared<GameObject>(mesh, shader);
        go->rotation = glm::vec3(
                glm::radians(g.rotationEuler.x),
                glm::radians(g.rotationEuler.y),
                glm::radians(g.rotationEuler.z)
                );
        go->position = g.position;
        go->scale = g.scale;
        go->color = g.color;

        if(g.parentId != -1){
            go->parent = gameObjects[g.parentId].get();
        }


        gameObjects.push_back(go);
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

                case SDLK_w:
                        cameraPosition.z += cameraSpeed;
                        break;
                    case SDLK_s:
                        cameraPosition.z += -cameraSpeed;
                        break;
                    case SDLK_a:
                        cameraPosition.x += -cameraSpeed;
                        break;
                    case SDLK_d:
                        cameraPosition.x += cameraSpeed;
                        break; 
                    case SDLK_q:
                        cameraPosition.y += -cameraSpeed;
                        break;
                    case SDLK_e:
                        cameraPosition.y += cameraSpeed;
                        break;

                }
            break;

        }

    }

    SimpleRenderEngine::instance->getCamera()->lookAt(cameraPosition, {0,0,0}, {0,1,0});

    // render game object
    for (auto & go : gameObjects){
        go->draw();
    }
    SimpleRenderEngine::instance->swapWindow();
}
