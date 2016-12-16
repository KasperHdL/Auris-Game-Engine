#pragma once

#include "Auris/Entities/PhysicsEntity.hpp"
#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Utilities/SpriteSheet.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Utilities/BodyStandard.hpp"

using namespace Auris;
using namespace Constants;

class Wall : public PhysicsEntity{
public:

    Sprite* sprite;

    Wall(vec2 position = vec2(0,0)):PhysicsEntity() {
        type = "Wall";

        SpriteSheet* spriteSheet = AssetManager::getSpriteSheet("MarioPacked.json");
        sprite = RenderSystem::getSprite(this);
        spriteSheet->setSpriteTo(sprite, "brick");

        b2PolygonShape shape; 
        shape.SetAsBox(sprite->getWidth() * PIXELS_TO_METERS/2, sprite->getHeight() * PIXELS_TO_METERS/2); 

        body = Auris::Utilities::BodyStandard::getStaticBody(&shape, position, 30.0f);

        // Physics properties
        setCollisionEvents(true);
    }

    ~Wall(){
        Auris::RenderSystem::deleteSprite(sprite);
    }
};
