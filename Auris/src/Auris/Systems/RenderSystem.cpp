#include "Auris/Systems/RenderSystem.hpp"

using namespace Auris;
Pool<Sprite> RenderSystem::spritePool = Pool<Sprite>();
vector<shared_ptr<Animation>> RenderSystem::animations;

void RenderSystem::startup(int reserve){
    RenderSystem::spritePool.initialize(reserve);
}

void RenderSystem::shutdown(){
    RenderSystem::animations.clear();
}


void RenderSystem::update(float dt){
    for(int i = 0; i < RenderSystem::spritePool.capacity;i++){
        Sprite* s = RenderSystem::spritePool[i];
        if(s != nullptr)
            s->draw();
    }

}

Sprite* RenderSystem::getSprite(GameObject* gameObject){
    Sprite* s = new (RenderSystem::spritePool.create()) Sprite(gameObject);
    return s;
}
Sprite* RenderSystem::getSprite(GameObject* gameObject, Material* material){
    Sprite* s = new (RenderSystem::spritePool.create()) Sprite(gameObject, material);
    return s;
}

shared_ptr<Animation> RenderSystem::getAnim(GameObject* gameObject, float length){
    shared_ptr<Animation> a = make_shared<Animation>(gameObject, length);
    RenderSystem::animations.push_back(a);
    return a;
}

void RenderSystem::deleteSprite(Sprite* sprite){
    RenderSystem::spritePool.remove(sprite);
}

void RenderSystem::deleteAnim(shared_ptr<Animation> ani){
    if(RenderSystem::animations.size() == 0){
        std::cout << "No Animations to delete" << std::endl;
        return;
    }

    int index = 0;
    for (auto& el : RenderSystem::animations){
        if(ani == el)
            break;
        index++;
    }
    RenderSystem::animations.erase(RenderSystem::animations.begin() + index);
}
