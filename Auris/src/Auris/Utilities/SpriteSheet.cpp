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

void SpriteSheet::setSpriteTo(Sprite* sprite, std::string name, bool getFlipped){
    if(meshes[(getFlipped ? "flipped_" : "") + name] == nullptr)
        std::cerr << "Error: Sprite was no found in spritesheet" << std::endl;

    sprite->setProperties(texture, glm::vec4(1), normalMap, meshes[(getFlipped ? "flipped_" : "") + name]);
}

}
