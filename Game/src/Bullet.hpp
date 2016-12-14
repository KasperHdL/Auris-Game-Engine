#pragma once
#include "Auris/Engine.hpp"

using namespace std;
using namespace Auris;

class Bullet : public GameObject {
public:
    int damage = 10;
    float movementSpeed = 10;

    Auris::Material* mat;

    Bullet(vec2 position) : GameObject(){
        name = "Bullet";

        mat->color = vec4(1);
//        mat->texture = SRE::Texture::createFromFile(Resource::getPath("data/bullet.png").c_str(), false);
        mat->texture = SRE::Texture::getWhiteTexture();
        mat->mesh = SRE::Mesh::createCube();

        sprite = Auris::RenderSystem::getSprite(this, mat);
        sprite->scale = vec2(1,1);

        b2PolygonShape shape;
        shape.SetAsBox(0.5f * Constants::PIXELS_TO_METERS, 0.1f * Constants::PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, position);

        // Physics properties
        setCollisionEvents(true);
        setFixedRotation(true);
        setGravity(0);
    }

    void Update(float dt) {
        applyForce(right * movementSpeed);
    }

};
