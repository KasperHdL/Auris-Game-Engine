#pragma once

#include "Auris/Entity.hpp"
#include "Auris/Entities/Camera.hpp"
#include "Auris/Utilities/AssetManager.hpp"
#include <SDL2/SDL_mixer.h>

using namespace Auris;

namespace Auris {

class AudioPlayer : public Entity {
private:
    vector<Mix_Music*> music;
    vector<Mix_Chunk*> sounds;

    int channel;

    int sound;
    int differenceX = 0;
    int differenceY = 0;
    int pan = 127;
    int distance = 0;

    float fadeX = 1.0f;
    float fadeY = 1.0f;

    bool debugDraw = false;

    Auris::Camera* listener;

public:
    AudioPlayer(Auris::Camera* listener = nullptr, int channel = -1, float fadeX = 1.0f, float fadeY = 1.0f) {
        name = "AudioListener";
        if (listener != nullptr)
            this->listener = listener;
        this->channel = channel;
        this->fadeX = fadeX;
        this->fadeY = fadeY;
    }

    void init() {
        sound = addSound(Auris::AssetManager::getDataPath("pistolShot.wav").c_str(), 128);
    }

    //! Sets the pan and master volume according to the relative distance between this AudioPlayer and its listener
    void update(float deltaTime) {
        if (listener != nullptr) {
            differenceX = 127 - (transform->position.x - listener->getPos().x)/(listener->getWidth()/254);
            differenceY = 127 - (transform->position.y - listener->getPos().y)/(listener->getHeight()/254);
            pan = differenceX < 0 ? 0: differenceX > 254 ? 254 : differenceX;
            Mix_SetPanning(channel, pan, 254-pan);

            distance = 0;

            if (differenceX < 100)
                distance += (100 - differenceX)*fadeX;
            else if (differenceX > 154)
                distance += (differenceX - 154)*fadeX;

            if (differenceY < 80)
                distance += (80 - differenceY)*fadeY;
            else if (differenceY > 174)
                distance += (differenceY - 174)*fadeY;

            distance = distance > 255 ? 255 : distance;

            Mix_SetDistance(channel, distance);
        }

        if (debugDraw) {

        }

        if (Auris::Input::keyHeld(Auris::Action::a)) {
            listener->setPos(vec2(listener->getPos().x-5, listener->getPos().y));
        }

        if (Auris::Input::keyHeld(Auris::Action::d)) {
            listener->setPos(vec2(listener->getPos().x+5, listener->getPos().y));
        }

        if (Auris::Input::keyHeld(Auris::Action::w)) {
            listener->setPos(vec2(listener->getPos().x, listener->getPos().y+5));
        }

        if (Auris::Input::keyHeld(Auris::Action::s)) {
            listener->setPos(vec2(listener->getPos().x, listener->getPos().y-5));
        }

        if (Auris::Input::keyDown(Auris::Action::enter)) {
            playSound(sound);
        }

        if (Auris::Input::keyDown(Auris::Action::space)) {
            debugDraw = !debugDraw;
        }
    }

    //! Adds music to this AudioPlayer.
    /*!
     * \param path Path to the music to be played
     * \param volume The initial volume of that music (0-128). If over 128, it will default to 128.
     * \return int The index of the music. Returns -1 on load error.*/
    int addMusic(const char* path, int volume) {
        music.push_back(Mix_LoadMUS(path));
        if (music[music.size()-1] == nullptr) {
            cout << "Nullptr: Failed to load \"" << path << "\". Make sure the path is correct." << endl;
            return -1;
        }

        Mix_VolumeMusic(volume);
        return music.size()-1;
    }

    //! Adds a sound to this AudioPlayer.
    /*!
     * \param path Path to the .wav file
     * \param volume The initial volume of that sound (0-128). If over 128, it will default to 128.
     * \return int The index of the sound. Returns -1 on load error.*/
    int addSound(const char* path, int volume) {
        sounds.push_back(Mix_LoadWAV(path));
        if (sounds[sounds.size()-1] == nullptr) {
            cout << "Nullptr: Failed to load \"" << path << "\". Make sure the path is correct." << endl;
            return -1;
        }

        Mix_VolumeChunk(sounds[sounds.size()-1], volume);
        return sounds.size()-1;
    }

    //! Plays music.
    /*!
     * \param index The index of the music.*/
    void playMusic(int index){
        if (sounds.size()-1 >= index)
            //If there is no music playing
            if( Mix_PlayingMusic() == 0 )
                Mix_PlayMusic( music[index], channel );
        else
            cout << "Nullptr: No music at this index (" << index << ")." << endl;
    }

    //! Plays a sound.
    /*!
     * \param index The index of the sound.*/
    void playSound(int index) {
        if (sounds.size()-1 >= index) {
            Mix_PlayChannel(channel, sounds[index], 0 );
        }
        else
            cout << "Nullptr: No sound at this index (" << index << ")." << endl;
    }

    //! Pauses music if music is playing.
    void pauseMusic() {
        if( Mix_PlayingMusic() == 1 )
            Mix_PauseMusic();
    }

    //! Resumes music if music is paused
    void resumeMusic() {
        if( Mix_PlayingMusic() == 1 )
            Mix_ResumeMusic();
    }

    //! Stops music if music is playing or paused
    void stopMusic() {
        if (Mix_PlayingMusic() == 1)
            Mix_HaltMusic();
    }

    //! Sets volume of currently playing music.
    /*!
     * \param volume The volume to set the music to.*/
    void setMusicVolume(int volume) {
        Mix_VolumeMusic(volume);
    }

    //! Sets volume of a sound.
    /*!
     * \param index The index of that sound
     * \param volume The volume to set it to.*/
    void setSoundVolume(int index, int volume) {
        if (sounds.size()-1 >= index) {
            Mix_VolumeChunk(sounds[index], volume);
        }
        else
            cout << "Nullptr: No sound at this index (" << index << ")." << endl;
    }

    //! Sets the channel this AudioPlayer plays in.
    //! If music or sounds are playing, they will keep playing in the old channel.
    //! Music needs to be halted and restarted in the new channel.
    /*!
     * \param int The new channel.*/
    void setChannel(int channel) {
        this->channel = channel;
    }

    //! Destructor
    ~AudioPlayer(){
        for (auto & element: music)
            Mix_FreeMusic(element);

        for (auto & element: sounds)
            Mix_FreeChunk(element);

        music.clear();
        sounds.clear();
    }
};
}
