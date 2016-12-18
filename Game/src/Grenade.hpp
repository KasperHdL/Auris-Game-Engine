#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Entities/PhysicsEntity.hpp"
#include "Auris/Systems/ParticleSystem.hpp"
#include "Auris/Utilities/BodyStandard.hpp"
#include "Auris/Utilities/Timer.hpp"
#include "Auris/Utilities/AudioPlayer.hpp"

using namespace Auris;

class Grenade : public PhysicsEntity{
public:
    Sprite* sprite;

    ParticleSystem* particles;

    Timer explodeTimer;
    Timer destroyTimer;

    AudioPlayer* audioPlayer;

    vec2 direction;

    int damage = 50;
    int explosionSound;
    int explosionRadius = 18;

    float explosionTime = 3;
    float destroyTime = 1;
    float speed = 20;

    bool hasExploded = false;

    Grenade(vec2 position = vec2(0, 0), vec2 direction = vec2(1,0), float force = 1){
        type = "Grenade";
        name = "Grenade";

        this->direction = direction;

        sprite = RenderSystem::getSprite(this, AssetManager::getTexture("grenade.png"));

        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = 0.1;

        body = Utilities::BodyStandard::getDynamicBody(&shape, position);
        explodeTimer.start(explosionTime);
        destroyTimer.start(destroyTime);

        // Physics properties
        this->speed *= force;
        setGravity(8);
    }

    void update(float deltaTime) {
        explodeTimer.update(deltaTime);
        if (explodeTimer.time()) {
            if (!hasExploded) {
                explode();
            }
        }
        if (destroyTimer.time(deltaTime) && hasExploded) {
            Game::instance->destroyEntity(this);
        }
    }

    void init() {
        audioPlayer = (AudioPlayer*) Game::instance->addEntity(make_shared<AudioPlayer>(Game::instance->camera, this, 1));
        applyForce(direction * speed, true);
        explosionSound = audioPlayer->addSound(AssetManager::getSound("expl.wav"));
    }

    void explode() {
        audioPlayer->playSound(explosionSound);
        type = "Explosion";

        RenderSystem::deleteSprite(sprite);

        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = explosionRadius;

        Engine::instance->world->DestroyBody(body);

        body = Utilities::BodyStandard::getStaticBody(&shape, transform->getPosition(), true);

        destroyTimer.reset();

        //particles->startup(1000, 3.0f);

        setCollisionEvents(true);

        hasExploded = true;
    }
};
