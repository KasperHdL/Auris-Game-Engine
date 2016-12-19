#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Entities/PhysicsEntity.hpp"
#include "Auris/Systems/ParticleSystem.hpp"
#include "Auris/Utilities/BodyStandard.hpp"
#include "Auris/Utilities/Timer.hpp"
#include "Auris/Entities/AudioPlayer.hpp"
#include <glm/gtc/random.hpp>

using namespace Auris;

class Grenade : public PhysicsEntity{
public:
    Sprite* sprite;

    Timer explodeTimer;
    Timer destroyTimer;

    AudioPlayer* audioPlayer;
    ParticleSystem* particleSystem;

    vec2 direction;

    int damage = 100;
    int explosionSound;
    int explosionRadius = 30;

    float explosionTime = 3;
    float destroyTime = .5f;
    float speed = 20;

    bool hasExploded = false;

    Grenade(vec2 position = vec2(0, 0), vec2 direction = vec2(1,0), float force = 1, int groupIndex = 0){
        type = "Grenade";
        name = "Grenade";

        this->direction = direction;

        sprite = RenderSystem::getSprite(this, AssetManager::getTexture("grenade.png"));

        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = 1;

        b2Filter filter;
        filter.groupIndex = groupIndex;

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape, false, 3.0f, 20.0f, 0.0f, &filter);
        explodeTimer.start(explosionTime);
        destroyTimer.start(destroyTime);

        setPosition(position);

        particleSystem = RenderSystem::getParticleSystem();
        particleSystem->startup(150,1.0f,SRE::Texture::getWhiteTexture());

        // Physics properties
        this->speed *= force;
        setGravity(8);
    }

    ~Grenade(){
        RenderSystem::deleteParticleSystem(particleSystem);
    }

    void update(float deltaTime) {
        explodeTimer.update(deltaTime);
        if (explodeTimer.time()) {
            if (!hasExploded) {
                explode();
            }
        }
        destroyTimer.update(deltaTime);
        if (destroyTimer.time() && hasExploded) {
            Game::instance->destroyEntity(this);
        }
    }

    void init() {
        audioPlayer = (AudioPlayer*) Game::instance->addEntity(make_shared<AudioPlayer>(Game::instance->camera, 1));
        addChild(audioPlayer);
        applyForce(direction * speed, true);
        explosionSound = audioPlayer->addSound(AssetManager::getSound("expl.wav"));
    }

    void explode() {
        audioPlayer->playSound(explosionSound);
        type = "Explosion";

        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = explosionRadius;

        //clean up sprite and old body
        RenderSystem::deleteSprite(sprite);
        Engine::instance->world->DestroyBody(body);
        //create new body
        body = Utilities::BodyStandard::getStaticBody(&shape, transform->getPosition(), true);

        destroyTimer.reset();

        //particles->startup(1000, 3.0f);

        setCollisionEvents(true);

        hasExploded = true;


        vec3 pos = transform->getGlobalPosition();
        float a = 0;
        float av = 0.5f;
        vec4 sc = vec4(1,0,0,1);
        float s = 0;
        vec4 ec = vec4(.5f,.25f,0,0);
        float es = 1;

        float linRand;
        vec3 cirRand;

        for(int i = 0;i < 150;i++){
            linRand = glm::linearRand<float>(0,1);
            cirRand = vec3(glm::circularRand<float>(linRand),0);
            particleSystem->emit(
                    pos,
                    cirRand * 20.0f,
                    linRand * 3.14f,
                    av + linRand,
                    sc + vec4(cirRand * 0.25f, 0),
                    s,
                    ec,
                    es
            );


        }
    }
};
