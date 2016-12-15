#pragma once

#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Texture.hpp"

#include <iostream>

#include "Auris/Utilities/Mesh.hpp"
#include "Auris/Utilities/Shader.hpp"
#include "Auris/Utilities/SpriteSheet.hpp"
#include "Auris/Entity.hpp"
#include "Auris/Entities/Nuggets/Sprite.hpp"

using namespace SRE;

namespace Auris{
class Animation : public Nugget {
public:

    std::vector<Mesh*> meshes;

    ~Animation();
    Animation(Entity* entity, float length);

    void addMesh(Mesh* mesh);
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
