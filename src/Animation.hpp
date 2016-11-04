#pragma once

#include "src\GameObjects\GameObject.hpp"
#include "src\GameObjects\Components\Sprite.hpp"
#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"

using namespace SRE;
class Animation
{
public:

	Texture* tex;
	std::vector<Texture*> textures;

	~Animation() {
		textures.clear();
	}
	void setTexture(Texture* tex);
	void delLastTexture();
	void updateAnim(float dt);

	Animation(GameObject* gameObject, float length){
		
		tex = gameObject->sprite->texture;
		this->length = length;
		frameLength = length / textures.size();
		index = 0;

	}

private:
	float length;
	float frameLength;
	float time;
	int index;
};