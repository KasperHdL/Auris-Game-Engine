#pragma once

#include "SRE/SimpleRenderEngine.hpp"
#include "SDL.h"
#include "Box2D/Box2D.h"
#include "SceneGraphImporter.hpp"

class Engine{
public:
    Engine(int width, int height):width(width),height(height){};
    virtual ~Engine(){};

    void startup();
    void shutdown();

    void run();

    void HandleSDLEvents();
    
private:

    int width;
    int height;
    int quit;
};


