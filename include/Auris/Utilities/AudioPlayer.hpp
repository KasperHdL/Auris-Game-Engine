#pragma once

#include <SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <vector>

namespace Auris {

class AudioPlayer {
private:
    vector<Mix_Music*> music;
    vector<Mix_Chunk*> sounds;

public:
    /*! Adds music to this AudioPlayer.
     * Takes the path to the music to be played and the initial volume of that music (0-128).
     * Returns the index of the music.*/
    int addMusic(const char* path, int volume) {
        music.push_back(Mix_LoadMUS(path));
        if (music[music.size()-1] == nullptr)
            cout << "Nullptr: Failed to load \"" << path << "\". Make sure the path is correct." << endl;
        Mix_VolumeMusic(volume);
        return music.size()-1;
    }

    /*! Adds a sound effect to this AudioPlayer.
     * Takes the path to the .wav file and the initial volume of that sound (0-128).
     * Returns the index of the sound.*/
    int addSound(const char* path, int volume) {
        sounds.push_back(Mix_LoadWAV(path));
        if (sounds[sounds.size()-1] == nullptr)
            cout << "Nullptr: Failed to load \"" << path << "\". Make sure the path is correct." << endl;
        Mix_VolumeChunk(sounds[sounds.size()-1], volume);
        return sounds.size()-1;
    }

    /*! Plays music. Takes the index of the music.*/
    void playMusic(int index){
        //If there is no music playing
        if( Mix_PlayingMusic() == 0 )
            //Play the music
            Mix_PlayMusic( music[index], -1 );
    }

    /*! Plays a sound. Takes the index of the sound.*/
    void playSound(int index) {
        Mix_PlayChannel(-1, sounds[index], 0 );
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

    /*! Sets volume of currently playing music.
     * Takes a volume.*/
    void setMusicVolume(int volume) {
        Mix_VolumeMusic(volume);
    }

    /*! Sets volume of a sound.
     * Takes index of that sound and a volume.*/
    void setSoundVolume(int index, int volume){
        Mix_VolumeChunk(sounds[index], volume);
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
