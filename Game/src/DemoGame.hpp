#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Entities/Camera.hpp"

#include "Scenes/Scene1.hpp"
#include "Scenes/Scene2.hpp"
#include "Auris/Utilities/AudioPlayer.hpp"
#include "Crosshair.hpp"
#include <vector>

using namespace Auris;

class DemoGame : public Auris::Game {
    Scene1 scene1;

    vector<int> controllers;

    vector<Player*> players;

    int pistolShot;
    int warSounds;

    int musicVolume = 128;
    int soundVolume = 128;

    void init() {
        Game::camera = new Auris::Camera(1280, 720);
        loadScene(&scene1);
        Engine::instance->world->SetGravity(b2Vec2(0, -9.8));

        controllers.resize(8);
        for (auto & element : controllers) {
            element = -1;
        }
    }

    void earlyUpdate(float dt){

    }

    void update(float dt){
        if (Input::keyDown(SDL_SCANCODE_RETURN))
            Game::destroyEntity(players[0]);

        int i = 0;
        vec2 camPos;
        for (auto & player : players) {
            camPos += vec2(player->transform->position.x*Constants::METERS_TO_PIXELS, player->transform->position.y*Constants::METERS_TO_PIXELS);
            i++;
        }

        if (i != 0) {
            camPos /= i;
            Game::camera->setPos(camPos);
        }
    }

    void lateUpdate(float dt){

    }

    void shutdown(){

    }

    void controllerConnected(){

    }

    void controllerActivated(int controllerID){
        int i = 0;
        for (auto & element : controllers) {
            if (element == -1) {
                element = controllerID;
                addPlayer(i, element);
                break;
            }
            i++;
        }
    }

    void addPlayer(int i, int controllerID){

        vec2 pos = i == 0 ? vec2(-40, -10) :
                i == 1 ? vec2(-40, 30) :
                i == 2 ? vec2(40, -10) :
                i == 3 ? vec2(40, 30):
                vec2(0, 0);

        auto player = (Player*) Game::instance->addEntity(make_shared<Player>(pos));
        player->setController(controllerID);
        player->name = player->type + to_string(controllerID);

        players.push_back(player);
    }


    void controllerDisconnected(int controllerID){
        for (auto & element : players) {
            if (element->controller == controllerID) {
                Game::destroyEntity(element);
            }
        }
    }

    void imGUI(){

    }
};
