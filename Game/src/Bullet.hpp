#pragma once
#include "Auris/Engine.hpp"

using namespace std;
using namespace Auris;

class Bullet : public GameObject {
public:
    int damage = 10;

    Bullet(){
        name = "Bullet";

        mat->color = vec4(1);
        mat->texture = SRE::createFromFile(Resources::getPath("bullet.png", false));
        mat->mesh = SRE::Mesh::createCube();

        sprite = Auris::RenderSystem::getSprite(this, mat);
        sprite->scale = vec2(1,1);

        b2PolygonShape shape;
        shape.SetAsBox(0.25f * Constants::PIXELS_TO_METERS, 0.1f * Constants::PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, position);

        // Physics properties
        setCollisionEvents(true);
        setFixedRotation(true);
    }

    void Update() {

    }

};
