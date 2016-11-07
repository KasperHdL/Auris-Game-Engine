#pragma once

#include "src/GameObjects/GameObject.hpp"
#include "src/GameObjects/Components/Sprite.hpp"
#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"

#include <iostream>

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
	Texture* getSprite();

	Animation(GameObject* gameObject, float length){
		
		tex = gameObject->sprite->texture;
		this->length = length;
		index = 0;
		time = 0;
		std::cout << this->length << " " << textures.size() << " " << frameLength << std::endl;

	}

private:
	float length;
	float frameLength;
	float time;
	int index;
};