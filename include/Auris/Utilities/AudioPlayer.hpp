#pragma once

#include "Auris/Entity.hpp"
#include "Auris/Entities/Camera.hpp"
#include "Auris/Utilities/Resource.hpp"
#include <SDL2/SDL_mixer.h>

using namespace Auris;

namespace Auris {

class AudioPlayer : public Entity {
private:
    vector<Mix_Music*> music;
    vector<Mix_Chunk*> sounds;

    int channel;

    int sound;
    int difference = 0;
    int pan = 127;
    int distance = 0;

    Auris::Camera* listener;

public:
    AudioPlayer(Auris::Camera* listener = nullptr, int channel = -1) {
        name = "AudioListener";
        if (listener != nullptr)
            this->listener = listener;
        this->channel = channel;
    }

    void init() {
        sound = addSound(Auris::Resource::getPath("pistolShot.wav").c_str(), 128);
    }

    void update(float deltaTime) {
        if (listener != nullptr) {
            difference = 127 - (transform->position.x - listener->getPos().x)/(listener->getWidth()/254);
            pan = difference < 0 ? 0: difference > 254 ? 254 : difference;
            Mix_SetPanning(channel, pan, 254-pan);
            if (difference < 100)
                distance = (100 - difference)*2;
            else if (difference > 154)
                distance = (difference - 154)*2;

            distance = distance > 255 ? 255 : distance;

            Mix_SetDistance(channel, distance);

            cout << "normalized pos: " << difference << endl;
            cout << "pan: " << pan << endl;
            cout << "distance: " << distance << endl;
        }

        if (Auris::Input::keyHeld(Auris::Action::a)) {
            listener->setPos(vec2(listener->getPos().x-5, listener->getPos().y));
        }

        if (Auris::Input::keyHeld(Auris::Action::d)) {
            listener->setPos(vec2(listener->getPos().x+5, listener->getPos().y));
        }

        if (Auris::Input::keyDown(Auris::Action::enter)) {
            playSound(sound);
        }
    }

    //! Adds music to this AudioPlayer.
    /*!
     * \param path Path to the music to be played
     * \param volume The initial volume of that music (0-128). If over 128, it will default to 128.
     * \return int The index of the music.*/
    int addMusic(const char* path, int volume) {
        music.push_back(Mix_LoadMUS(path));
        if (music[music.size()-1] == nullptr)
            cout << "Nullptr: Failed to load \"" << path << "\". Make sure the path is correct." << endl;
        Mix_VolumeMusic(volume);
        return music.size()-1;
    }

    //! Adds a sound to this AudioPlayer.
    /*!
     * \param path Path to the .wav file
     * \param volume The initial volume of that sound (0-128). If over 128, it will default to 128.
     * \return int The index of the sound.*/
    int addSound(const char* path, int volume) {
        sounds.push_back(Mix_LoadWAV(path));
        if (sounds[sounds.size()-1] == nullptr)
            cout << "Nullptr: Failed to load \"" << path << "\". Make sure the path is correct." << endl;
        Mix_VolumeChunk(sounds[sounds.size()-1], volume);
        return sounds.size()-1;
    }

    //! Plays music.
    /*!
     * \param index The index of the music.*/
    void playMusic(int index){
        //If there is no music playing
        if( Mix_PlayingMusic() == 0 )
            //Play the music
            Mix_PlayMusic( music[index], channel );
    }

    //! Plays a sound.
    /*!
     * \param index The index of the sound.*/
    void playSound(int index) {
        Mix_PlayChannel(channel, sounds[index], 0 );
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
        Mix_VolumeChunk(sounds[index], volume);
    }

    //! Sets the channel this AudioPlayer plays in.
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
