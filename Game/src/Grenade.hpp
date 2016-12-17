#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Entities/PhysicsEntity.hpp"
#include "Auris/Systems/ParticleSystem.hpp"
#include "Auris/Utilities/BodyStandard.hpp"
#include "Auris/Utilities/Timer.hpp"

using namespace Auris;

class Grenade : public PhysicsEntity{
public:
    Sprite* sprite;
    ParticleSystem* particles;
    Timer timer;
    b2Body* sensor;

    vec2 direction;

    int damage;
    float explosionRadius;
    float speed;
    bool hasExploded = false;

    Grenade(vec2 position = vec2(0, 0), vec2 direction = vec2(1,0)){
        type = "Grenade";

        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = 1;

        body = Utilities::BodyStandard::getDynamicBody(&shape, position);
        timer.start(3);

        // Physics properties
        speed = 2000;
    }

    void update(float deltaTime) {
        if (timer.time(deltaTime)) {
            if (!hasExploded) {
                type = "Explosion";

                Engine::instance->world->DestroyBody(body);
                RenderSystem::deleteSprite(sprite);

                b2CircleShape shape;
                shape.m_p.Set(0, 0);
                shape.m_radius = 3;

                b2FixtureDef fixtureDef;
                fixtureDef.shape = &shape;
                fixtureDef.isSensor = true;

                particles->startup(1000, 3.0f);

                hasExploded = true;
            }
        }
    }

    void init() {
        applyForce(direction * speed, true);
    }


};
