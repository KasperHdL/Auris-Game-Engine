#pragma once

#include "Auris/Entities/PhysicsEntity.hpp"
#include "Auris/Utilities/Timer.hpp"
#include "Auris/Utilities/BodyStandard.hpp"
#include "Auris/Utilities/AssetManager.hpp"
#include "Auris/Utilities/AudioPlayer.hpp"

#include <glm/gtc/random.hpp>

using namespace glm;
using namespace Auris;

class SoundEntity : public PhysicsEntity {
public:
    AudioPlayer* audioPlayer;

    Timer destroyTimer;

    SoundEntity(Mix_Chunk* sound) {
        audioPlayer = (AudioPlayer*) Game::instance->addEntity(make_shared<AudioPlayer>(Game::instance->camera, 1, 1, 1));
        addChild(audioPlayer);

        b2CircleShape shape;
        shape.m_p.Set(0, 0);
        shape.m_radius = 0.1;

        vec2 position = circularRand<float>(100);
        float speed = linearRand<float>(0.5f, 1);

        body = Utilities::BodyStandard::getDynamicBody(&shape, position);
        applyForce(-position*speed, true);
        destroyTimer.start(4);

        int index = audioPlayer->addSound(sound);
        audioPlayer->playSound(index);
    }

    void update(float deltaTime) {
        destroyTimer.update(deltaTime);
        if (destroyTimer.time()) {
            Game::instance->destroyEntity(this);
        }
    }

    ~SoundEntity() {
    }

};
