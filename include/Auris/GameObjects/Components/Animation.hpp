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

    std::vector<Material*> materials;

    ~Animation();
     Animation(GameObject* gameObject, float length);

    void addMaterial(Material* mat);
    void setSheet(SpriteSheet* spritesheet);
    void makeSequence(SpriteSheet* spritesheet, string name);
    void run(Sprite* sprite, float dt);

private:
	float length;
	float frameLength;
	float time;
	int index;
};
}
