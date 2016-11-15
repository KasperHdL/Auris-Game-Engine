#include "RenderSystem.hpp"

Pool<Sprite> RenderSystem::spritePool = Pool<Sprite>();

void RenderSystem::startup(int reserve){
    RenderSystem::spritePool.initialize(reserve);

}

void RenderSystem::shutdown(){
}


void RenderSystem::update(float dt){
    int i = 0;
    for(Sprite* s = RenderSystem::spritePool.begin(); s != RenderSystem::spritePool.end(); s++){
        s->draw();
        i++;
    }
}


Sprite* RenderSystem::getSprite(GameObject* gameObject){
    Sprite* s = new (RenderSystem::spritePool.create()) Sprite(gameObject);

    return s;
}

void RenderSystem::deleteSprite(Sprite* sprite){
    RenderSystem::spritePool.remove(sprite);

}
