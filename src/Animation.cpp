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

void Animation::draw()
{
	texture = textures.at(0);
	Shader* shader = Shader::getUnlitSprite();
    shader->setVector("color", color);
    shader->setTexture("tex", texture);
	SimpleRenderEngine::instance->draw(mesh, gameObject->globalTransform(), shader);

}

