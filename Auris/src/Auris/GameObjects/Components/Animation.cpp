#include "Auris/GameObjects/Components/Animation.hpp"
using namespace Auris;

Animation::Animation(GameObject *gameObject, float length){
    this->length = length;
    Animation::index = 0;
    Animation::time = 0;
}

Animation::~Animation(){
    Animation::materials.clear();
}

void Animation::addMaterial(Material* mat){
    materials.push_back(mat);
}

void Animation::setSheet(SpriteSheet* spritesheet){
    for(map<std::string,Material*>::iterator it = spritesheet->sprites.begin(); it != spritesheet->sprites.end(); ++it) {
        addMaterial(it->second);
    }
}

void Animation::makeSequence(SpriteSheet* spritesheet, string name){
    for(map<std::string,Material*>::iterator it = spritesheet->sprites.begin(); it != spritesheet->sprites.end(); ++it) {
        //cout << name << " : " << it->first << endl;
        if(!it->first.compare(0,name.size(),name)){
        addMaterial(it->second);
        }
    }
}

void Animation::run(Sprite *sprite, float dt){
    frameLength = length / materials.size();
    time += dt;
    if (time >= frameLength) {
        index++;
        if (index >= materials.size()) {
            index = 0;
        }
        time = glm::mod<float>(time, frameLength);
    }
    sprite->setMaterial(materials[index]);
}

