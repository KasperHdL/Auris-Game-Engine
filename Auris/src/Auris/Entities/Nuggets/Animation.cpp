#include "Auris/Entities/Nuggets/Animation.hpp"
using namespace Auris;

Animation::Animation(Entity *entity, float length):Nugget(entity){
    this->length = length;
    Animation::index = 0;
    Animation::time = 0;
}

Animation::~Animation(){
    meshes.clear();
}

void Animation::addMesh(Mesh* mesh){
    meshes.push_back(mesh);
}

void Animation::setSheet(SpriteSheet* spritesheet){
    for(std::map<std::string,Mesh*>::iterator it = spritesheet->meshes.begin(); it != spritesheet->meshes.end(); ++it) {
        addMesh(it->second);
    }
}

void Animation::makeSequence(SpriteSheet* spritesheet, std::string name){
    for(std::map<std::string,Mesh*>::iterator it = spritesheet->meshes.begin(); it != spritesheet->meshes.end(); ++it) {
        //cout << name << " : " << it->first << endl;
        if(!it->first.compare(0,name.size(),name)){
            addMesh(it->second);
        }
    }
}

void Animation::run(Sprite *sprite, float dt){
    frameLength = length / meshes.size();
    time += dt;
    if (time >= frameLength) {
        index++;
        if (index >= meshes.size()) {
            index = 0;
        }
        time = glm::mod<float>(time, frameLength);
    }
    sprite->mesh = meshes[index];
}

