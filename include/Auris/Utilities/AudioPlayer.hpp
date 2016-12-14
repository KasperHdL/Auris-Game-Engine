#pragma once

#include <SDL2/SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>

namespace Auris {

class AudioPlayer {
private:
    vector<Mix_Music*> music;
    vector<Mix_Chunk*> sfx;

public:
    /*! Add music to this AudioPlayer. Returns the index needed for playing this music.*/
    void addMusic(char* path, float volume, bool music) {
        sfx.push_back(Mix_LoadMUS(&path));
        return sfx.length()-1;
    }

    /*! Add a sound effect to this AudioPlayer. Returns the index needed for playing this sound effect.*/
    void addSoundEffect(char* path, float volume, bool music) {
        sfx.push_back(Mix_LoadWAV(&path));
        return sfx.length()-1;
    }

    /*! Play piece of music. Takes the index of the music.*/
    void playMusic(int index){
        //If there is no music playing
        if( Mix_PlayingMusic() == 0 )
            //Play the music
            Mix_PlayMusic( music[index], -1 );
    }

    /*! Play a sound effect. Takes the index of the sound effect.*/
    void playSoundEffect(int index) {
        Mix_PlayChannel(-1, sfx[index], 0 );
    }

    ~AudioPlayer(){
        for (auto & element: music)
            Mix_FreeMusic(element);

        for (auto & element: sfx)
            Mix_FreeChunk(element);
    }
};
}
