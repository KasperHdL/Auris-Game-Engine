#pragma once

#include <vector>
#include <memory>
#include "glm/glm.hpp"
#include "GameObject.hpp"

#include "SDL.h"

class Engine {
public:
    void setup();
    void start();
private:
    void update(float deltaTimeSec);
    std::vector<std::shared_ptr<GameObject>> gameObjects;

    bool _gameRunning = true;

    glm::vec3 cameraPosition;
    float cameraSpeed;

};


