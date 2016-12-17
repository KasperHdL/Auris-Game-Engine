#pragma once

#include "Auris/Entities/PhysicsEntity.hpp"
#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Utilities/SpriteSheet.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Utilities/BodyStandard.hpp"

using namespace Auris;
using namespace Constants;

class WallSprite : public Entity {
public:
    Sprite* sprite;

    WallSprite(vec2 position = vec2(0, 0)) {
        sprite = RenderSystem::getSprite(this, AssetManager::getTexture("concreteSmall.png"), nullptr, AssetManager::getTexture("concreteSmallNormal.png"));
    }
};

class HorizontalWall : public PhysicsEntity{
public:
    vector<Sprite*> sprites;

    int width;

    HorizontalWall(vec2 position = vec2(0,0)):PhysicsEntity() {
        type = "Wall";

        width = Game::instance->camera->getWidth();

        for (int i = 0; i <= width; i += 32) {
            Sprite* sprite;

            sprite = RenderSystem::getSprite(this, AssetManager::getTexture("concreteSmall.png"), nullptr, AssetManager::getTexture("concreteSmallNormal.png"));
            sprite->offset = vec3(-width/(float)2+i-16, 0, 0);
            sprites.push_back(sprite);
        }

        b2PolygonShape shape;
        shape.SetAsBox(width * PIXELS_TO_METERS/2, 64*PIXELS_TO_METERS/2);
        cout << sprites[0]->getHeight() << endl;

        body = Auris::Utilities::BodyStandard::getStaticBody(&shape, position, 30.0f);

        // Physics properties
        setCollisionEvents(true);
    }

    ~HorizontalWall(){
    }
};

class VerticalWall : public PhysicsEntity{
public:
    float height;

    VerticalWall(vec2 position = vec2(0,0)):PhysicsEntity() {
        type = "Wall";

        height = Game::instance->camera->getHeight();

        b2PolygonShape shape;
        shape.SetAsBox(64*PIXELS_TO_METERS/2, height * PIXELS_TO_METERS/2);

        body = Auris::Utilities::BodyStandard::getStaticBody(&shape, position, 30.0f);

        for (int i = 0; i <= height; i += 32) {
            addChild(Game::instance->addEntity(make_shared<WallSprite>(vec2(0, -height/2 * PIXELS_TO_METERS/2 + i))));
        }

        // Physics properties
        setCollisionEvents(true);
    }

    ~VerticalWall(){
    }
};
