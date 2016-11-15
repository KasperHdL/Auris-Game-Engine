#pragma once

#include <vector>
#include <memory>

#include "GameObjects/GameObject.hpp"
#include "GameObjects/Components/Sprite.hpp"
#include "Utility/Pool.hpp"

using namespace std;
class RenderSystem{
    public:

    static Pool<Sprite> spritePool;
    
    RenderSystem(){};
    ~RenderSystem(){};

    void startup(int reserve);

    void shutdown();
    void update(float dt);
    
    static Sprite* getSprite(GameObject* gameObject);
    static void deleteSprite(Sprite* sprite);
};
