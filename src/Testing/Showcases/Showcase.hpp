#pragma once

struct Showcase{
    Showcase(){};
    ~Showcase(){};

    virtual void imGui() = 0;
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
};
