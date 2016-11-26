#pragma once

class Game {

public:
    virtual void init() = 0;

    virtual void earlyUpdate(float dt) = 0;

    virtual void update(float dt) = 0;

    virtual void lateUpdate(float dt) = 0;

    virtual void shutdown() = 0;
};
