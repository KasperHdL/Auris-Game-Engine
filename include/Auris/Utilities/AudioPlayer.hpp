#pragma once

#include <SDL2/SDL.h>
#include "AudioClip.hpp"
#include <string>

namespace Auris {
class AudioPlayer {
public:
    virtual void audioCallback(void *userdata, Uint8 *stream, int len){}

    static Uint8 *audio_pos; //! Global pointer to the audio buffer
    static Uint32 audio_len; //! Remaining length of the audio

    int playSound(char* path){
        if (SDL_Init(SDL_INIT_AUDIO) < 0)
                return 1;

        static Uint32 wav_length; // length of sample
        static Uint8 *wav_buffer; // buffer containing audio file
        static SDL_AudioSpec wav_spec; // the specs of the audioclip

        /* Load the WAV */
        // the specs, length and buffer of our wav are filled
        if( SDL_LoadWAV(path, &wav_spec, &wav_buffer, &wav_length) == NULL )
          return 1;

        // set the callback function
        wav_spec.callback = audioCallback;
        wav_spec.userdata = NULL;

        // set global static variables
        audio_pos = wav_buffer; // copy sound buffer
        audio_len = wav_length; // copy file length

        /* Open the audio device */
        if ( SDL_OpenAudio(&wav_spec, NULL) < 0 ){
          fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
          exit(-1);
        }

        /* Start playing */
        SDL_PauseAudio(0);

        // wait until we're not playing
        while ( audio_len > 0 ) {
            SDL_Delay(100);
        }

        SDL_CloseAudio();
        SDL_FreeWAV(wav_buffer);
    }

    AudioPlayer(){}
    ~AudioPlayer(){
        delete audio_pos;
    }

    void audioCallback(void *userdata, Uint8 *stream, int len) {
        if (audio_len ==0)
            return;

        len = ( len > audio_len ? audio_len : len );
        //SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
        SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

        audio_pos += len;
        audio_len -= len;
    }
};



}
