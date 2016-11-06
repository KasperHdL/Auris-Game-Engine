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
	std::cout << index  << std::endl;
	if (time >= frameLength) {
		index++;
		if (index >= textures.size()) {
			index = 0;
		}
		Texture temp = *textures[index];
		*tex = temp;
		time = glm::mod<float>(time, frameLength);
	}
}

