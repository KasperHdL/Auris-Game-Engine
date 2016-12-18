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

    int width;

    Wall(vec2 position, int numTilesX, int numTilesY, string type):PhysicsEntity() {
        this->type = type;
        name = "Wall";

        auto tex = AssetManager::getTexture("concreteSmall.png");

        float w = tex->getWidth();
        float h = tex->getHeight();

        float nhw = -w/2;
        float nhh = -h/2;

        //quad
        std::vector<glm::vec3> vertices({
            glm::vec3{ w + nhw, nhh, 0 }, 
            glm::vec3{ w + nhw, h + nhh, 0 },
            glm::vec3{ nhw, nhh, 0 },

            glm::vec3{ nhw, nhh, 0 }, 
            glm::vec3{ w + nhw, h + nhh, 0 }, 
            glm::vec3{ nhw, h + nhh, 0 }
        });

        // Per pixel normals are used for 2D graphics, but the mesh still needs an empty normal vector
        std::vector<glm::vec3> normals;

        // UVs contains the normalized texture coordinates.

        std::vector<glm::vec2> uvs({
            glm::vec2{ numTilesX, 0 }, glm::vec2{ numTilesX, numTilesY }, glm::vec2{ 0, 0 },
            glm::vec2{ 0, 0 }, glm::vec2{numTilesX, numTilesY }, glm::vec2{ 0, numTilesY }
        });

        Auris::Mesh* mesh = new Auris::Mesh(vertices, normals, uvs ,w, h);

        sprite = RenderSystem::getSprite(this,tex, mesh, AssetManager::getTexture("concreteSmallNormal.png"));
        transform->setScale(vec2(numTilesX, numTilesY));

        b2PolygonShape shape;
        shape.SetAsBox((numTilesX * w) * Constants::PIXELS_TO_METERS/2, (numTilesY * h) * Constants::PIXELS_TO_METERS/2);

        body = Auris::Utilities::BodyStandard::getStaticBody(&shape, position, 0.0f);

        b2PolygonShape edge;
        edge.SetAsBox((((numTilesX * w)) * Constants::PIXELS_TO_METERS/2)-0.5f, 0.1f);
        b2Body* upper;
        upper = Auris::Utilities::BodyStandard::getStaticBody(&edge, vec2(position.x,position.y+1.5f), 30.0f);

        // Physics properties
        upper->SetUserData(this);
        //setCollisionEvents(true);
    }

    ~Wall(){
    }
};
