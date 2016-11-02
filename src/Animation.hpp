#pragma once

#include "src\GameObjects\Components\Sprite.hpp"
#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"

using namespace SRE;
class Animation : public SpriteTexture
{
public:

	std::vector<Texture*> textures;

	~Animation() {
		textures.clear();
	}
	void setTexture(Texture* tex);
	void delLastTexture();
	void draw();

	Animation(GameObject* gameObject):SpriteTexture(gameObject) {}

private:

};