#pragma once

#include <vector>
#include <memory>

#include "GameObjects/GameObject.hpp"
#include "GameObjects/Components/Sprite.hpp"

using namespace std;
class RenderSystem{
    public:

    static vector<shared_ptr<Sprite>> sprites;
    
    RenderSystem(){};
    ~RenderSystem(){};

    void startup(int reserve);

    void shutdown();
    void update(float dt);
    

    static shared_ptr<Sprite> getSprite(GameObject* gameObject);
    static shared_ptr<SpriteTexture> getSpriteTexture(GameObject* gameObject);
	static shared_ptr<Animation> getSpriteAnimation(GameObject* gameObject, float length);
};
