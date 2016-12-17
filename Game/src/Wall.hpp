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
    vector<Sprite*> sprites;

    int width;

    Wall(vec2 position = vec2(0,0)):PhysicsEntity() {
        type = "Wall";

        width = Game::instance->camera->getWidth();

        b2PolygonShape shape;
        shape.SetAsBox(width * PIXELS_TO_METERS/2, Game::instance->camera->getWidth() * PIXELS_TO_METERS/2);

        cout << "Camera width: " << width * PIXELS_TO_METERS/2;

        for (int i = 0; i < width * PIXELS_TO_METERS/2; i += 2) {
            Sprite* sprite;
            sprite->offset = vec3(width*PIXELS_TO_METERS/2+i, 0, 0);

            sprite = RenderSystem::getSprite(this, AssetManager::getTexture("concrete.png"), nullptr, AssetManager::getTexture("concreteNormal.png"));
            sprites.push_back(sprite);
            cout << "i: " << i;
        }

        body = Auris::Utilities::BodyStandard::getStaticBody(&shape, position, 30.0f);

        // Physics properties
        setCollisionEvents(true);
    }

    ~Wall(){
        Auris::RenderSystem::deleteSprite(sprite);
    }
};
