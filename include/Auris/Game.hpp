#pragma once

#include "Auris/Engine.hpp"
namespace Auris{
class Game {

public:
    virtual void init() = 0;

    virtual void earlyUpdate(float dt) = 0;

    virtual void update(float dt) = 0;

    virtual void lateUpdate(float dt) = 0;

    virtual void debugDraw(){}


    virtual void shutdown() = 0;

    virtual void controllerConnected(int controllerID) = 0;

    virtual void controllerDisconnected(int controllerID) = 0;
};
}
