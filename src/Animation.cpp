#include "Animation.hpp"
#include "src\GameObjects\GameObject.hpp"

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
	time += dt;

	if (time >= frameLength) {
		index++;
		if (index >= textures.size()) {
			index = 0;
		}
		tex = textures[index];
		time = glm::mod<float>(time, frameLength);
	}
}

//void animation::draw() {
//
//	shader* shader = shader::getunlitsprite();
//    shader->setvector("color", color);
//    shader->settexture("tex", texture);
//	simplerenderengine::instance->draw(mesh, gameobject->globaltransform(), shader);
//}

