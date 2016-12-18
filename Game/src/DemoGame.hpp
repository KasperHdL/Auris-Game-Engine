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

    AudioPlayer* audioPlayer;

    int pistolShot;
    int warSounds;
    int music;

    int musicVolume = 128;
    int soundVolume = 128;

    vec2 cameraDesiredPos = vec2(0);

    void init() {
        Game::camera = new Auris::Camera(1280, 720);
        loadScene(&scene1);
        Engine::instance->world->SetGravity(b2Vec2(0, -9.8));

        audioPlayer = (AudioPlayer*) addEntity(make_shared<AudioPlayer>(nullptr, 5));
        music = audioPlayer->addMusic(AssetManager::getMusic("electronicMusic.wav"), 60);
        audioPlayer->playMusic(music);

        controllers.resize(8);
        for (auto & element : controllers) {
            element = -1;
        }
    }

    void earlyUpdate(float dt){

    }

    float map (float value, float from1, float to1, float from2, float to2) {
        return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
    }

    void update(float dt){

        float amountOfZoom = 1;
        if(players.size()==1){
            cameraDesiredPos = players[0]->transform->getPosition();
        }else if(players.size()>1){
            float distx = -1;
            float disty = -1;
            for(int i = 0; i<players.size();i++){
                for(int j = i+1; j<players.size();j++){

                    vec2 player1 = players[i]->transform->getPosition();
                    vec2 player2 = players[j]->transform->getPosition();

                    vec2 delta = player2 - player1;

                    if(distx < glm::abs(delta.x)){
                        distx = glm::abs(delta.x);
                        cameraDesiredPos.x = delta.x/2.0f+player1.x;
                    }

                    if(disty < glm::abs(delta.y)){
                        disty = glm::abs(delta.y);
                        cameraDesiredPos.y = delta.y/2.0f+player1.y;
                    }

                    //cout << "i: " << i << " j: " << j << " x: " << distx << " ,y: " << disty<< endl;

                }

            }
            amountOfZoom = map(distx + disty,1,100,0.4f,1);
        }
        vec2 camPos = Game::camera->getPos()*Constants::PIXELS_TO_METERS;
        vec2 delta = cameraDesiredPos - camPos;
        delta *= 0.1f;
        camPos += delta;


        Game::camera->zoom(amountOfZoom);
        //cout << "X: " << camPos.x << " Y: " << camPos.y << endl;
        Game::camera->setPos(camPos * Constants::METERS_TO_PIXELS);

        if (Input::keyHeld(Action::m)) {
            audioPlayer->stopMusic();
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

        //Bow before Mathias' cancer vector
        vec2 pos = i == 0 ? vec2(-40, -10) :
                i == 1 ? vec2(-50, 30) :
                i == 2 ? vec2(40, -10) :
                i == 3 ? vec2(50, 30):
                vec2(0, 0);

        //Bow before Jonas' cancer vector
        vec4 col = i == 0 ? vec4(1,1,1,1) :
                   i == 1 ? vec4(0,1,0,1) :
                   i == 2 ? vec4(0,0,1,1) :
                   i == 3 ? vec4(1,0,1,1) :
                   vec4(1,1,1,1);

        auto player = (Player*) Game::instance->addEntity(make_shared<Player>(pos,col));
        player->setController(controllerID);
        player->name = player->type + to_string(controllerID);

        players.push_back(player);
    }


    void controllerDisconnected(int controllerID){
        int i = 0;
        for (auto & element : players) {
            if (element->controller == controllerID) {
                Game::destroyEntity(element);
                players.erase(players.begin() + i);
            }
            i++;
        }
    }

};
