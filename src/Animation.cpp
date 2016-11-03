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
		texture = textures[index];
		time = glm::mod<float>(time, frameLength);
	}
}

void Animation::draw() {

	Shader* shader = Shader::getUnlitSprite();
    shader->setVector("color", color);
    shader->setTexture("tex", texture);
	SimpleRenderEngine::instance->draw(mesh, gameObject->globalTransform(), shader);
}

