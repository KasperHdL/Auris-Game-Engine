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
    auto s = RenderSystem::getSprite(parent, meshes[name], texture, normalMap);
    return s;
}

}
