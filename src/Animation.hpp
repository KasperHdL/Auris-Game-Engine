#pragma once

#include "src/GameObjects/GameObject.hpp"
#include "src/GameObjects/Components/Sprite.hpp"
#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"
#include "SpriteSheet.hpp"

#include <iostream>

using namespace SRE;
class Animation
{
public:

	std::vector<Texture*> textures;
    std::vector<Mesh*> meshes;

	~Animation() {
		textures.clear();
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
		std::cout << this->length << " " << textures.size() << " " << frameLength << std::endl;

	}

private:
	float length;
	float frameLength;
	float time;
	int index;
};
