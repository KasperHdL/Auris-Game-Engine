#pragma once

#include "Auris/Engine.hpp"

#include "Scenes/Scene1.hpp"
#include "Scenes/Scene2.hpp"


class DemoGame : public Auris::Game {
    Scene1 scene1;
    AudioPlayer audioPlayer;
    int pistolShot;

    void init() {
        Auris::Engine::loadScene(&scene1);
        Auris::Engine::world->SetGravity(b2Vec2(0, -9.8));
        pistolShot = audioPlayer.addSoundEffect("../../data/pistolShot.wav", 1.0f);
    }

    void earlyUpdate(float dt){

    }

    void update(float dt){
        if (Input::keyDown(SDL_SCANCODE_SPACE)){
            audioPlayer.playSoundEffect(pistolShot);
        }
    }

    void lateUpdate(float dt){

    }

    void shutdown(){

    }

    virtual void controllerConnected(){

    }

    virtual void controllerDisconnected(){

    }
};
