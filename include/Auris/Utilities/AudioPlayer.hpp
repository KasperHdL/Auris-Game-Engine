#pragma once

#include "Auris/Entity.hpp"
#include "Auris/Entities/Camera.hpp"
#include "Auris/Utilities/AssetManager.hpp"
#include "Auris/Systems/Input.hpp"

#ifdef _WIN32 // Windows
#include <SDL_mixer.h>
#elif __linux__ // Linux
#include <SDL2/SDL_mixer.h>
#else
cout << "Error: Unsupported OS" << endl;
#endif

using namespace Auris;

namespace Auris {

//! The AudioPlayer class that extend the Entity class
    /*! Used to create audio entities, so that audio can be used in a game
    */
class AudioPlayer : public Entity {
private:
    std::vector<Mix_Music*> music; /*!< A vector of Mix_Music pointers: music. Instance of the music in the audioplayer. */
    std::vector<Mix_Chunk*> sounds; /*!< A vector of Mix_Chunk pointers: sounds. Instance of the sound in the audioplayer. */

    int channel; /*!< An int value: channel. The channel to play the sound/music. */

    int deltaDistanceX = 0; /*!< An int value: deltaDistanceX. The relative distance between the audio and the audio listener on the x axis. */
    int deltaDistanceY = 0; /*!< An int value: deltaDistanceY. The relative distance between the audio and the audio listener on the y axis. */
    int pan = 127; /*!< An int value: pan. How much pan the channel the audio is playing at should have. */
    int fade = 0; /*!< An int value: face. How much face the channel the audio is playing at should have. */

    float fadeScaleX = 1.0f; /*!< A float value: faceScaleX. The scaling on the fade on the x axis. */
    float fadeScaleY = 1.0f; /*!< A float value: faceScaleY. The scaling on the fade on the y axis. */
    float fadeDelayX = 1.0f; /*!< A float value: faceDelayX. The delay of the fade on the x axis. */
    float fadeDelayY = 1.0f; /*!< A float value: faceDelayY. The delay of the fade on the y axis. */

    Auris::Camera* listener; /*!< A Camera* pointer: listener. The camera that should listen for the audio. */

public:

    //! The AudioPlayer constructor, taking 0-6 arguments.
            /*!
             * Initializes AudioPlayer to the values inputted.
             * \param listener a Camera pointer. The camera that should be the listener (default no listener, meaning global audio).
             * \param channel an int value. The channel that the audio should play to (default is the first open channel (loses control of the audio)).
             * \param fadeScaleX a float value. The scale which to face by on the x axis (default is 1.0).
             * \param fadeScaleY a float value. The scale which to face by on the y axis (default is 1.0).
             * \param fadeDelayX a float value. The delay of the fade on the x axis (default is 0).
             * \param fadeDelayY a float value. The delay of the fade on the y axis (default is 0).
            */
    AudioPlayer(Auris::Camera* listener = nullptr, int channel = -1, float fadeScaleX = 1.0f, float fadeScaleY = 1.0f, int fadeDelayX = 0, int fadeDelayY = 0) {
        type = "AudioPlayer";

        if (listener != nullptr)
            this->listener = listener;

        this->channel = channel;

        this->fadeScaleX = fadeScaleX;
        this->fadeScaleY = fadeScaleY;

        this->fadeDelayX = fadeDelayX;
        this->fadeDelayY = fadeDelayY;
    }

    /*! An update method, taking 1 argument.
    /*! Sets the pan and master volume according to the relative distance between this AudioPlayer and its listener
     * \param deltaTime a float value. The delta time in seconds.
     */
    void update(float deltaTime) {
        if (listener != nullptr) {
            deltaDistanceX = 127 - (transform->getGlobalPosition().x - listener->getPos().x)/(listener->getWidth()/254);
            deltaDistanceY = 127 - (transform->getGlobalPosition().y - listener->getPos().y)/(listener->getHeight()/254);
            pan = deltaDistanceX < 0 ? 0: deltaDistanceX > 254 ? 254 : deltaDistanceX;
            Mix_SetPanning(channel, pan, 254-pan);

            fade = 0; // 0 is near, 255 is far

            if (deltaDistanceX < (127 - fadeDelayX))
                fade += ((127 - fadeDelayX) - deltaDistanceX)*fadeScaleX;
            else if (deltaDistanceX > (127 + fadeDelayX))
                fade += (deltaDistanceX - (127 + fadeDelayX))*fadeScaleX;

            if (deltaDistanceY < (127 - fadeDelayY))
                fade += ((127 - fadeDelayY) - deltaDistanceY)*fadeScaleY;
            else if (deltaDistanceY > (127 + fadeDelayY))
                fade += (deltaDistanceY - (127 + fadeDelayY))*fadeScaleY;

            fade = fade > 255 ? 255 : fade;

            Mix_SetDistance(channel, fade);
        }
    }

    /*! An addMusic method, taking 1-2 arguemnts.
        * Adds music to this AudioPlayer.
        * \param mixMusic a Mix_Music pointer. The music to add to the audioplayer. Use AssetManager::getMusic() to get the pointer.
        * \param volume an int value. The initial volume of that music (0-128) (default is 128).
        * \return int. The index of the music. Returns -1 on load error.
        * \sa addSound()
        * \sa AssetManager::getMusic()
        */
    int addMusic(Mix_Music* mixMusic, int volume = 128) {
        music.push_back(mixMusic);

        Mix_VolumeMusic(volume);
        return music.size()-1;
    }

    /*! An addSound method. taking 1-2 arguments.
     * Adds a sound to this AudioPlayer.
     * \param mixChunk a Mix_Chunk pointer. The sound to add to the audioplayer. Use AssetManager::getSound() to get the pointer
     * \param volume an int value. The initial volume of that sound (0-128) (default is 128).
     * \return int The index of the sound. Returns -1 on load error.
     * \sa addMusic()
     * \sa AssetManager::getSound() */
    int addSound(Mix_Chunk* mixChunk, int volume = 128) {
        sounds.push_back(mixChunk);

        Mix_VolumeChunk(sounds[sounds.size()-1], volume);
        return sounds.size()-1;
    }

    /*! A playMusic method, taking 1 argument.
     * Plays the music of the AudioPlayer
     * \param index an int value. The index of the music.*/
    void playMusic(int index){
        if (music.size()-1 >= index){
            //If there is no music playing
            if( Mix_PlayingMusic() == 0 ){
                Mix_PlayMusic( music[index], channel );
            }
        }else{
            std::cout << "Nullptr: No music at this index (" << index << ")." << std::endl;
        }
    }

    /*! A playSound method, taking 1 argument.
     * Plays the sound of the AudioPlayer
     * \param index an int value. The index of the sound.*/
    void playSound(int index) {
        if (sounds.size()-1 >= index) {
            Mix_PlayChannel(channel, sounds[index], 0 );
        }else{
            std::cout << "Nullptr: No sound at this index (" << index << ")." << std::endl;
        }
    }

    /*! A pauseMusic method.
     * Pauses music if music is playing
     */
    void pauseMusic() {
        if( Mix_PlayingMusic() == 1 )
            Mix_PauseMusic();
    }

    /*! A resumeMusic method.
     * Resumes playing music if music is paused
     */
    void resumeMusic() {
        if( Mix_PlayingMusic() == 1 )
            Mix_ResumeMusic();
    }

    /*! A stopMusic method.
     * Stops all music playing or paused.
     */
    void stopMusic() {
        if (Mix_PlayingMusic() == 1)
            Mix_HaltMusic();
    }

    /*! A setMusicVolume method, taking 1 argument.
     * Sets volume of currently playing music.
     * \param volume an int value. The volume to set the music to.*/
    void setMusicVolume(int volume) {
        Mix_VolumeMusic(volume);
    }

    /*! A setSoundVolume method, taking 2 arguments.
     * Sets volume of a sound
     * \param index an int value. The index of that sound
     * \param volume an int value. The volume to set it to.*/
    void setSoundVolume(int index, int volume) {
        if (sounds.size()-1 >= index) {
            Mix_VolumeChunk(sounds[index], volume);
        }
        else
            std::cout << "Nullptr: No sound at this index (" << index << ")." << std::endl;
    }

    /*! A setChannel method, taking 1 argument.
     * Sets the channel this AudioPlayer plays in.
     * If music or sounds are playing, they will keep playing in the old channel.
     * Music needs to be halted and restarted in the new channel.
     * \param channel an int value. The new channel.*/
    void setChannel(int channel) {
        this->channel = channel;
    }

    //! The AudioPlayer destructor.
        /*!
         * Clears all music and sounds.
        */
    ~AudioPlayer(){
        music.clear();
        sounds.clear();
    }


    ///////////
    // DEBUG
    //////

    bool drawAudioRange = true; /*!< A bool value: drawAudioRange. If the audio debug range should be draw. */
    float audioIconScale = 10; /*!< A float value: audioIconScale. The scale of the debug audio icon (default is 10). */

    /*! A debugDraw overload method.
     * Draws sound related debug information to the screen
     * \overload Entity::debugDraw()
     */
    void debugDraw(){
        float scale = audioIconScale;
        vec2 p = transform->getGlobalPosition() * Constants::METERS_TO_PIXELS;

        // Icon
        SRE::Debug::setColor(vec4(1,1,1,1));
        SRE::Debug::drawLine(vec3(p.x - scale, p.y + scale,0), vec3(p.x, p.y + scale,0));
        SRE::Debug::drawLine(vec3(p.x, p.y + scale,0), vec3(p.x + scale, p.y + scale*2,0));
        SRE::Debug::drawLine(vec3(p.x + scale, p.y + scale * 2,0), vec3(p.x + scale, p.y - scale*2,0));
        SRE::Debug::drawLine(vec3(p.x + scale, p.y - scale * 2,0), vec3(p.x, p.y - scale,0));
        SRE::Debug::drawLine(vec3(p.x , p.y - scale,0), vec3(p.x - scale, p.y - scale,0));
        SRE::Debug::drawLine(vec3(p.x - scale, p.y - scale,0), vec3(p.x - scale, p.y + scale,0));

        SRE::Debug::setColor(vec4(1,0,0,1));

        if (drawAudioRange) {
            // Range
            float minX = p.x - (fadeScaleX * listener->getWidth()/2) - fadeDelayX*Constants::METERS_TO_PIXELS/2;
            float maxX = p.x + (fadeScaleX * listener->getWidth()/2) + fadeDelayX*Constants::METERS_TO_PIXELS/2;
            float minY = p.y - (fadeScaleY * listener->getHeight()/2) - fadeDelayY*Constants::METERS_TO_PIXELS/2;
            float maxY = p.y + (fadeScaleY * listener->getHeight()/2) + fadeDelayY*Constants::METERS_TO_PIXELS/2;

            float line_len = 30;

            SRE::Debug::drawLine(vec3(minX, p.y,0), vec3(maxX, p.y,0));
            SRE::Debug::drawLine(vec3(p.x, minY,0), vec3(p.x, maxY, 0));

            SRE::Debug::drawLine(vec3(minX, p.y - line_len, 0), vec3(minX, p.y + line_len, 0));
            SRE::Debug::drawLine(vec3(maxX, p.y - line_len, 0), vec3(maxX, p.y + line_len, 0));
            SRE::Debug::drawLine(vec3(p.x - line_len, minY, 0), vec3(p.x + line_len, minY, 0));
            SRE::Debug::drawLine(vec3(p.x - line_len, maxY, 0), vec3(p.x + line_len, maxY, 0));
        }

    }


    /*! A inspectorImGui overload method.
     * Writes sound related debug information to the inspector
     * \overload Entity::inspectorImGui()
     */
    void inspectorImGui(){
        Entity::inspectorImGui();
        ImGui::Separator();

        ImGui::Text("Channel %d", channel); 
        ImGui::Text("Distance(in Fade Units)(%d,%d)", deltaDistanceX, deltaDistanceY);
        ImGui::Text("Current Fade: (%f,%f)", fade);
        ImGui::Text("Pan: %d", pan);

        ImGui::Separator();
        ImGui::Checkbox("Draw Audio Range", &drawAudioRange);
        ImGui::DragFloat("Audio Icon Scale", &audioIconScale);

    }
};
}
