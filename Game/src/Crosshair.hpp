#pragma once

#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Entities/Nuggets/Animation.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Entities/Nuggets/Material.hpp"
#include "Auris/Utilities/SpriteSheet.hpp"
#include "Auris/Utilities/BodyStandard.hpp"
#include "Auris/Utilities/AssetManager.hpp"
#include "Auris/Entities/PhysicsEntity.hpp"
#include "Auris/Action.hpp"

using namespace std;
using namespace Auris;

class Crosshair : public Entity {
public:
    Sprite* sprite;

    float distance = 10;

    Crosshair() {
        type = "crosshair";

        //sprite = RenderSystem::getSprite(this, AssetManager::getTexture("crosshair.png"));
        transform->scale *= 20;
    }
};
