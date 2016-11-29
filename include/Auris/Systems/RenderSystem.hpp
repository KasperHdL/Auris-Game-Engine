#pragma once

#include <vector>
#include <memory>

#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/Utilities/Pool.hpp"
#include "Auris/GameObjects/Components/Animation.hpp"

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

    static Sprite* getSprite(GameObject* gameObject);
    static Sprite* getSprite(GameObject* gameObject, Material* material);
    static void deleteSprite(Sprite* sprite);
	static shared_ptr<Animation> getAnim(GameObject* gameObject, float length);
    static void deleteAnim(shared_ptr<Animation> ani);
};
}
