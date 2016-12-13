#pragma once

#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"

#include <iostream>

#include "Auris/Entity.hpp"
#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Entities/Nuggets/SpriteSheet.hpp"

using namespace SRE;

namespace Auris{
class Animation : public Nugget {
public:

    std::vector<Material*> materials;

    ~Animation();
    Animation(Entity* entity, float length);

    void addMaterial(Material* mat);
    void setSheet(SpriteSheet* spritesheet);
    void makeSequence(SpriteSheet* spritesheet, std::string name);
    void run(Sprite* sprite, float dt);

private:
	float length;
	float frameLength;
	float time;
	int index;
};
}
