#pragma once

#include <string>
#include <map>
#include "SRE/Texture.hpp"

#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Utilities/picojson.h"
#include "Auris/Entities/Nuggets/Material.hpp"


namespace Auris{
class SpriteSheet{
    public:
        SpriteSheet(std::string pathToJSON);
        ~SpriteSheet();
        Sprite* getSprite(std::string name, Entity* parent);
        std::map<std::string,Material*> sprites;

    private:
        Material* saveMaterial(int x, int y, int width, int height, float anchorX, float anchorY);
        SRE::Texture* texture;
        SRE::Texture* normalMap = nullptr;

};
}
