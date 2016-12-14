#include "Auris/Systems/AssetSystem.hpp"

namespace Auris{

std::map<std::string, SRE::Texture*> AssetSystem::textures;

SRE::Texture* AssetSystem::getTexture(std::string path){
    if(AssetSystem::textures[path] == nullptr){
        AssetSystem::textures[path] = SRE::Texture::createFromFile(getDataPath(path).c_str(), false);
    }
    return AssetSystem::textures[path];
}

}
