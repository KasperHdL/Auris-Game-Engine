#include "Auris/Utilities/AudioPlayer.hpp"

namespace Auris {

int AudioPlayer::channelCount = 0;

AudioPlayer::AudioPlayer(Auris::Camera* listener, int channels, float fadeScaleX, float fadeScaleY, int fadeDelayX, int fadeDelayY){
    type = "AudioPlayer";

    this->listener = listener;
    if (listener != nullptr) {
        drawAudioRange = true;
    }

    this->fadeScaleX = fadeScaleX;
    this->fadeScaleY = fadeScaleY;

    this->fadeDelayX = fadeDelayX;
    this->fadeDelayY = fadeDelayY;

    Mix_AllocateChannels(channels+AudioPlayer::channelCount);

    this->channels.resize(channels);

    for (int i = 0; i < channels; i++) {
        this->channels[i] = i + AudioPlayer::channelCount;
    }

    this->currentChannel = 0;

    AudioPlayer::channelCount += channels;
}
}
