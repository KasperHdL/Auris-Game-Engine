#pragma once

#include "Auris/Entity.hpp"
#include "Auris/Entities/Camera.hpp"
#include "Auris/Utilities/AssetManager.hpp"
#include "Auris/Systems/Input.hpp"
#include <SDL2/SDL_mixer.h>

using namespace Auris;

namespace Auris {

class AudioPlayer : public Entity {
private:
    std::vector<Mix_Music*> music;
    std::vector<Mix_Chunk*> sounds;

    int channel;

    int deltaDistanceX = 0;
    int deltaDistanceY = 0;
    int pan = 127;
    int fade = 0;

    float fadeScaleX = 1.0f;
    float fadeScaleY = 1.0f;
    float fadeDelayX = 1.0f;
    float fadeDelayY = 1.0f;

    Auris::Camera* listener;

public:
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

    //! Sets the pan and master volume according to the relative distance between this AudioPlayer and its listener
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

    //! Adds music to this AudioPlayer.
    /*!
     * \param mixMusic The Mix_Music pointer, use AssetManager::getMusic() to get the pointer
     * \param volume The initial volume of that music (0-128). If over 128, it will default to 128.
     * \return int The index of the music. Returns -1 on load error.
     * \sa addSound()
     * \sa AssetManager::getMusic()
     */
    int addMusic(Mix_Music* mixMusic, int volume = 128) {
        music.push_back(mixMusic);

        Mix_VolumeMusic(volume);
        return music.size()-1;
    }

    //! Adds a sound to this AudioPlayer.
    /*!
     * \param mixChunk The Mix_Chunk pointer, use AssetManager::getSound() to get the pointer
     * \param volume The initial volume of that sound (0-128). If over 128, it will default to 128.
     * \return int The index of the sound. Returns -1 on load error.
     * \sa addMusic()
     * \sa AssetManager::getSound()
     */
    int addSound(Mix_Chunk* mixChunk, int volume = 128) {
        sounds.push_back(mixChunk);

        Mix_VolumeChunk(sounds[sounds.size()-1], volume);
        return sounds.size()-1;
    }

    //! Plays music.
    /*!
     * \param index The index of the music.*/
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

    //! Plays a sound.
    /*!
     * \param index The index of the sound.*/
    void playSound(int index) {
        if (sounds.size()-1 >= index) {
            Mix_PlayChannel(channel, sounds[index], 0 );
        }else{
            std::cout << "Nullptr: No sound at this index (" << index << ")." << std::endl;
        }
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
            std::cout << "Nullptr: No sound at this index (" << index << ")." << std::endl;
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
        music.clear();
        sounds.clear();
    }


    ///////////
    // DEBUG
    //////

    bool drawAudioRange = true;
    float audioIconScale = 10;

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
