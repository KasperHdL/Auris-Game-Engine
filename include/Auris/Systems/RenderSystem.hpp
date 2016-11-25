#pragma once

#include <vector>
#include <memory>

#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/Utility/Pool.hpp"
#include "Auris/GameObjects/Components/Animation.hpp"

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
    static void deleteSprite(Sprite* sprite);
	static shared_ptr<Animation> getAnim(GameObject* gameObject, float length);
};
