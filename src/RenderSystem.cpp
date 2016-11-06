#include "RenderSystem.hpp"

vector<shared_ptr<Sprite>> RenderSystem::sprites;
vector<shared_ptr<Animation>> RenderSystem::animations;

void RenderSystem::startup(int reserve){
    RenderSystem::sprites.reserve(reserve);

}

void RenderSystem::shutdown(){
    RenderSystem::sprites.clear();

}


void RenderSystem::update(float dt){
    for(auto& el : RenderSystem::sprites)
        el->draw();
	for (auto& el : RenderSystem::animations)
		el->updateAnim(dt);
}

shared_ptr<Sprite> RenderSystem::getSprite(GameObject* gameObject){
    shared_ptr<Sprite> s = make_shared<Sprite>(gameObject);
    sprites.push_back(s);

    return s;
}

shared_ptr<Animation> RenderSystem::getAnim(GameObject* gameObject, float length){
    shared_ptr<Animation> a = make_shared<Animation>(gameObject, length);
    animations.push_back(a);
    return a;
}

//shared_ptr<SpriteTexture> RenderSystem::getSpriteTexture(GameObject* gameObject){
//    shared_ptr<SpriteTexture> s = make_shared<SpriteTexture>(gameObject);
//    sprites.push_back(s);
//
//    return s;
//}

