#pragma once

#include <vector>
#include <memory>

#include "GameObjects/GameObject.hpp"
#include "GameObjects/Components/Sprite.hpp"
#include "src\Animation.hpp"

using namespace std;
class RenderSystem{
    public:

    static vector<shared_ptr<Sprite>> sprites;
	static vector<shared_ptr<Animation>> animations;
    
    RenderSystem(){};
    ~RenderSystem(){};

    void startup(int reserve);

    void shutdown();
    void update(float dt);
    

    static shared_ptr<Sprite> getSprite(GameObject* gameObject);
   // static shared_ptr<SpriteTexture> getSpriteTexture(GameObject* gameObject);
	static shared_ptr<Animation> getAnim(GameObject* gameObject, float length);
};
