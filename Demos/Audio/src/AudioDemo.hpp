#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Entities/AudioPlayer.hpp"
#include "Auris/Utilities/AssetManager.hpp"
#include "Auris/Testing/DebugUI.hpp"
#include "SoundEntity.hpp"

#include "SRE/imgui_sre.hpp"
#include <vector>

#include "glm/glm.hpp"

using namespace glm;
using namespace Auris;

class AudioDemo : public Game {
public:
    AudioPlayer* musicPlayer;
    vector<AudioPlayer*> soundPlayers;
    vector<int> music;
    vector<vector<int>> sounds;
    vector<Mix_Chunk*> yells;

    int musicVolume = 64;
    int pan = 127;
    int selectedPlayer = 4;
    int yell = 0;
    int musicPick = 0;

    float fadeScaleX = 1.0f;
    float fadeScaleY = 1.0f;
    float fadeDelayX = 1.0f;
    float fadeDelayY = 1.0f;


    bool showPlay = true;

    void init() {
        #ifdef DEBUG
        Engine::instance->debugUI->enableDebug();
        #endif

        Game::instance->camera = new Auris::Camera(Constants::width, Constants::height);

        musicPlayer = (AudioPlayer*) Game::instance->addEntity(make_shared<AudioPlayer>());

        music.push_back(musicPlayer->addMusic(AssetManager::getMusic("electronicMusic.wav")));
        music.push_back(musicPlayer->addMusic(AssetManager::getMusic("introLoop.wav")));
        music.push_back(musicPlayer->addMusic(AssetManager::getMusic("drumLoop.wav")));
        music.push_back(musicPlayer->addMusic(AssetManager::getMusic("time.wav")));

        soundPlayers.resize(5);
        sounds.resize(5);

        for (int i = 0; i < 5; i++) {
            AudioPlayer* soundPlayer = (AudioPlayer*) Game::instance->addEntity(make_shared<AudioPlayer>(camera, 1, 0.5, 0.5));
            soundPlayer->name = "Soundplayer" + to_string(i);
            soundPlayers[i] = soundPlayer;

            sounds[i].push_back(soundPlayers[i]->addSound(AssetManager::getSound("pistolShot.wav")));
            sounds[i].push_back(soundPlayers[i]->addSound(AssetManager::getSound("expl.wav")));
            sounds[i].push_back(soundPlayers[i]->addSound(AssetManager::getSound("fizzle.wav")));
        }

        soundPlayers[0]->transform->setPosition(vec2(-50, -25));
        soundPlayers[1]->transform->setPosition(vec2(-50, 25));
        soundPlayers[2]->transform->setPosition(vec2(50, -25));
        soundPlayers[3]->transform->setPosition(vec2(50, 25));
        soundPlayers[4]->transform->setPosition(vec2(0, 0));

        for (int i = 0; i < 5; i++) {
            std::cout << i << ": " << std::endl;
            for (int j = 0; i < 3; i++) {
                std::cout << "sound: " << sounds[i][j] << std::endl;
            }
        }

        yells.resize(4);
        yells[0] = AssetManager::getSound("yell1.mp3");
        yells[1] = AssetManager::getSound("yell3.mp3");
        yells[2] = AssetManager::getSound("scream0.wav");
        yells[3] = AssetManager::getSound("scream1.wav");
    }

    void spawnSoundEntity() {
        SoundEntity* soundEntity = (SoundEntity*) Game::instance->addEntity(make_shared<SoundEntity>(yells[yell]));
        yell = yell == yells.size()-1 ? 0 : yell+1;
    }

    void earlyUpdate(float deltaTime) {

    }

    void update(float deltaTime) {
        musicPlayer->setMusicVolume(musicVolume);

        for (auto & element : soundPlayers) {
            element->setFadeScaleX(fadeScaleX);
            element->setFadeScaleY(fadeScaleY);
            element->setFadeDelayX(fadeDelayX);
            element->setFadeDelayY(fadeDelayY);
        }

        vec2 camPos = camera->getPos();

        if (Input::keyHeld(Action::w)) {
            camera->setPos(vec2(camPos.x, camPos.y+5));
        }

        if (Input::keyHeld(Action::a)) {
            camera->setPos(vec2(camPos.x-5, camPos.y));
        }

        if (Input::keyHeld(Action::s)) {
            camera->setPos(vec2(camPos.x, camPos.y-5));
        }

        if (Input::keyHeld(Action::d)) {
            camera->setPos(vec2(camPos.x+5, camPos.y));
        }
    }

    void lateUpdate(float deltaTime) {

    }

    void drawDebugImGui(){
        ImGui::Begin("Audio Player");
 
        ImGui::Separator();

        ImGui::TextColored(ImVec4(0, 0, 1, 1), "There is one music player and five sound players in the scene.\nPick sounds in this panel and play them.\nYou can also move the camera around using WASD.\n\nClick the button below to spawn a sound entity.");

        ImGui::Separator();

        if(ImGui::Button("Spawn sound entity")) {
            spawnSoundEntity();
        }

        ImGui::Separator();
        ImGui::Separator();

        ImGui::TextColored(ImVec4(1,0,0,1), "Music");

        ImGui::Separator();

        ImGui::Text("Pick music:");

        if (ImGui::Button("electronicMusic.wav")) {
            musicPlayer->playMusic(music[0]);
            showPlay = false;
        }

        if (ImGui::Button("introLoop.wav")) {
            musicPlayer->playMusic(music[1]);
            showPlay = false;
        }

        if (ImGui::Button("drumLoop.wav")) {
            musicPlayer->playMusic(music[2]);
            showPlay = false;
        }

        if (ImGui::Button("time.wav")) {
            musicPlayer->playMusic(music[3]);
            showPlay = false;
        }

        ImGui::Separator();

        if(showPlay){
            if(Mix_PlayingMusic()){
                if(ImGui::Button("Resume")){
                    musicPlayer->resumeMusic();
                    showPlay = false;
                }
            }else{
                if(ImGui::Button("Play Random")){
                    musicPlayer->playMusic(music[glm::linearRand<int>(0,3)]);
                    showPlay = false;
                }
            }
        }else{
            if(ImGui::Button("Pause")){
                musicPlayer->pauseMusic();
                showPlay = true;
            }
        }

        ImGui::SameLine();

        if(ImGui::Button("Stop")){
            musicPlayer->stopMusic();
            showPlay = true;
        }

        ImGui::Separator();

        ImGui::SliderInt("Music volume", &musicVolume, 0, 128);

        ImGui::Separator();
        ImGui::Separator();
        ImGui::Separator();

        ImGui::TextColored(ImVec4(1,0,0,1), "Sounds");

        ImGui::Separator();

        ImGui::Text("Play sound:");

        if (ImGui::Button("Pistol shot")) {
            soundPlayers[selectedPlayer]->playSound(sounds[selectedPlayer][0]);
        }

        ImGui::SameLine();

        if (ImGui::Button("Explosion")) {
            soundPlayers[selectedPlayer]->playSound(sounds[selectedPlayer][1]);
        }

        ImGui::SameLine();

        if (ImGui::Button("Fizzle")) {
            soundPlayers[selectedPlayer]->playSound(sounds[selectedPlayer][2]);
        }

        ImGui::Text("Select sound location: ");

        if (ImGui::Button("Top-left")) {
            selectedPlayer = 1;
        }

        ImGui::SameLine();

        if (ImGui::Button("Top-right")) {
            selectedPlayer = 3;
        }

        if (ImGui::Button("Middle")) {
            selectedPlayer = 4;
        }

        if (ImGui::Button("Bottom-left")) {
            selectedPlayer = 0;
        }

        ImGui::SameLine();

        if (ImGui::Button("Bottom-right")) {
            selectedPlayer = 2;
        }

        {
        ImGui::Text("Fade scale for sound players: ");
        ImGui::DragFloat("X-axis fade scale", &fadeScaleX, 0.05f, 0.1f, 20.0f);
        ImGui::DragFloat("Y-axis fade scale", &fadeScaleY, 0.05f, 0.1f, 20.0f);
        }

        {
        ImGui::Text("Fade delay for sound players: ");
        ImGui::DragFloat("X-axis fade delay", &fadeDelayX, 0.05f, 0.1f, 20.0f);
        ImGui::DragFloat("Y-axis fade delay", &fadeDelayY, 0.05f, 0.1f, 20.0f);
        }
        ImGui::Separator();

        ImGui::End();

    }

    void shutdown() {
        music.clear();
        sounds.clear();
    }

};
