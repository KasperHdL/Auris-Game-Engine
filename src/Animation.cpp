#include "Animation.hpp"

void Animation::setTexture(Texture* tex)
{
	textures.push_back(tex);
}

void Animation::delLastTexture()
{
	textures.pop_back();
}

void Animation::updateAnim(float dt)
{
	frameLength = length / textures.size();
	time += dt;
	if (time >= frameLength) {
		index++;
		if (index >= textures.size()) {
			index = 0;
		}
		time = glm::mod<float>(time, frameLength);
	}
}

Texture* Animation::getSprite()
{
	return textures[index];
}

