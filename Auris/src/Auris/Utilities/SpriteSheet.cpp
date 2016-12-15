#include "Auris/Utilities/SpriteSheet.hpp"
#include "Auris/Systems/RenderSystem.hpp"

namespace Auris{
using namespace std;
SpriteSheet::SpriteSheet(){

}

SpriteSheet::~SpriteSheet(){

    for(map<std::string, Auris::Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it){
        delete it->second;
        it->second = nullptr;
    }

    meshes.clear();

    texture = nullptr;
    normalMap = nullptr;
}

Sprite* SpriteSheet::getSprite(string name, Entity* parent){
    if(meshes[name] == nullptr)
        std::cerr << "Error: Sprite was no found in spritesheet" << std::endl;
    auto s = RenderSystem::getSprite(parent, texture, meshes[name], normalMap);

    return s;
}

}
