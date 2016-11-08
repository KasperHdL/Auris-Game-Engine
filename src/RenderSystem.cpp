#include "RenderSystem.hpp"

Pool<Sprite> RenderSystem::spritePool = Pool<Sprite>();
vector<shared_ptr<Animation>> RenderSystem::animations;

void RenderSystem::startup(int reserve){
    RenderSystem::spritePool.initialize(reserve);

}

void RenderSystem::shutdown(){
}


void RenderSystem::update(float dt){
	for (auto& el : RenderSystem::animations)
		el->updateAnim(dt);
    int i = 0;
    for(Sprite* s = RenderSystem::spritePool.begin(); s != RenderSystem::spritePool.end(); s++){
        i++;
        s->draw();
}


Sprite* RenderSystem::getSprite(GameObject* gameObject){
    Sprite* s = new (RenderSystem::spritePool.create()) Sprite(gameObject);

    return s;
shared_ptr<Animation> RenderSystem::getAnim(GameObject* gameObject, float length){
    shared_ptr<Animation> a = make_shared<Animation>(gameObject, length);
    animations.push_back(a);
    return a;
}
