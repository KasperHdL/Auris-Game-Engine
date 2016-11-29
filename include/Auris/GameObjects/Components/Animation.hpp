#pragma once

#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"

#include <iostream>

#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/GameObjects/Components/SpriteSheet.hpp"

using namespace SRE;

namespace Auris{
class Animation
{
public:

	std::vector<Texture*> textures;
    std::vector<Mesh*> meshes;

	~Animation() {
		textures.clear();
        meshes.clear();
	}
	void setTexture(Texture* tex);
    void setSheet(SpriteSheet* spritesheet);
    void setMesh(Mesh* mesh);
	void delLastTexture();
    void delLastMest();
	void updateAnim(float dt);
    Texture* getSprite();
    void setSprite(Sprite* sprite);

	Animation(GameObject* gameObject, float length){
		
		this->length = length;
		index = 0;
		time = 0;

	}

private:
	float length;
	float frameLength;
	float time;
	int index;
};
}
