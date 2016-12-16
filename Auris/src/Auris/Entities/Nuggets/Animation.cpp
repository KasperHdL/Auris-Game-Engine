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

void Animation::makeSequence(SpriteSheet* spritesheet, std::string name, bool createFlipped){
    for(std::map<std::string,Mesh*>::iterator it = spritesheet->meshes.begin(); it != spritesheet->meshes.end(); ++it) {
        //cout << name << " : " << it->first << endl;
        if(!it->first.compare(0,name.size(),name)){
            meshes.push_back(it->second);
        }
        if(createFlipped && !it->first.compare(0,("flipped_" + name).size(),"flipped_" + name)){
            flipped_meshes.push_back(it->second);
        }

    }
}

void Animation::run(Sprite *sprite, float dt, bool getFlipped){
    frameLength = length / meshes.size();
    time += dt;
    if (time >= frameLength) {
        index++;
        if (index >= meshes.size()) {
            index = 0;
        }
        time = glm::mod<float>(time, frameLength);
    }
    if(getFlipped)
        sprite->mesh = flipped_meshes[index];
    else
        sprite->mesh = meshes[index];
}

