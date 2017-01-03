#pragma once

#include "Auris/Auris.hpp"

using namespace std;
using namespace Auris;

class Crosshair : public Entity {
public:
    Sprite* sprite;

    float distance = 10;

    Crosshair() {
        type = "crosshair";

        sprite = RenderSystem::getSprite(this, AssetManager::getTexture("crosshair.png"));
        transform->setScale(vec2(0.5f, 0.5f));
    }

    ~Crosshair() {
        RenderSystem::deleteSprite(sprite);
    }
};
