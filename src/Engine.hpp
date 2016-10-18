#pragma once

#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"
#include "SDL.h"
#include "Box2D/Box2D.h"

#include <memory>
#include "GameObject.hpp"

class Engine{
public:
    Engine(int width, int height):width(width),height(height){};
    virtual ~Engine(){};

    void startup();
    void shutdown();

    void run();

    void HandleSDLEvents();
    
private:

    GameObject* g;

    int width;
    int height;
    int quit;
};


