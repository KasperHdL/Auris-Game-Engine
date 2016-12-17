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

    Timer timer;

    b2Body* sensor;

    AudioPlayer* audioPlayer;

    vec2 direction;

    int damage;
    int explosion;

    float explosionTime = 3;
    float explosionRadius;
    float speed;

    bool hasExploded = false;

    Grenade(vec2 position = vec2(0, 0), vec2 direction = vec2(1,0)){
        type = "Grenade";
        name = "Grenade";

        sprite = RenderSystem::getSprite(this, AssetManager::getTexture("grenade.png"));

        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = 1;

        body = Utilities::BodyStandard::getDynamicBody(&shape, position);
        timer.start(explosionTime);

        // Physics properties
        speed = 8000;
    }

    void update(float deltaTime) {
        if (timer.time(deltaTime)) {
            if (!hasExploded) {
                audioPlayer->playSound(explosion);
                type = "Explosion";

                Engine::instance->world->DestroyBody(body);
                RenderSystem::deleteSprite(sprite);

                b2CircleShape shape;
                shape.m_p.Set(0, 0);
                shape.m_radius = 3;

                b2FixtureDef fixtureDef;
                fixtureDef.shape = &shape;
                fixtureDef.isSensor = true;

                sensor->CreateFixture(&fixtureDef);

                //particles->startup(1000, 3.0f);

                hasExploded = true;
            }
        }
    }

    void init() {
        audioPlayer = (AudioPlayer*) Game::instance->addEntity(make_shared<AudioPlayer>(Game::instance->camera, 1));
        addChild(audioPlayer);
        applyForce(direction * speed, true);
        explosion = audioPlayer->addSound(AssetManager::getSound("expl.wav"));
    }


};
