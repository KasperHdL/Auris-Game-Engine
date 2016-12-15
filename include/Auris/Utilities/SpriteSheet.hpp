#pragma once

#include <string>
#include <map>
#include "SRE/Texture.hpp"
#include "Auris/Utilities/Mesh.hpp"

#include "Auris/Entities/Nuggets/Sprite.hpp"


namespace Auris{
class SpriteSheet{
    public:
        SpriteSheet();
        ~SpriteSheet();
        Sprite* getSprite(std::string name, Entity* parent);

        std::map<std::string, Auris::Mesh*> meshes;
        SRE::Texture* texture;
        SRE::Texture* normalMap = nullptr;

};
}
