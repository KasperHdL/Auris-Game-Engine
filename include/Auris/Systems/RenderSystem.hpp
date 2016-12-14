#pragma once

#include <vector>
#include <memory>

#include "Auris/Entity.hpp"
#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Entities/Nuggets/Animation.hpp"
#include "Auris/Utilities/Pool.hpp"

#include "Auris/Utilities/Mesh.hpp"
#include "SRE/Texture.hpp"

namespace Auris{
using namespace std;
class RenderSystem{

public:
    static Pool<Sprite> spritePool;
    static vector<shared_ptr<Animation>> animations;

    RenderSystem(){}
    ~RenderSystem(){}

    void startup(int reserve);

    void shutdown();
    void update(float dt);

    static Sprite* getSprite(Entity* entity);
    static Sprite* getSprite(Entity* entity, Auris::Mesh* mesh, SRE::Texture* texture, SRE::Texture* normalMap = nullptr);
    static void deleteSprite(Sprite* sprite);
	static shared_ptr<Animation> getAnim(Entity* entity, float length);
    static void deleteAnim(shared_ptr<Animation> ani);
};
}
