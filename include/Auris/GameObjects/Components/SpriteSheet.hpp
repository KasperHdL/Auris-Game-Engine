#pragma once

#include <string>
#include <map>
#include "SRE/Texture.hpp"

#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/Utilities/picojson.h"
#include "Auris/GameObjects/Components/Material.hpp"


namespace Auris{
class SpriteSheet{
    public:
        SpriteSheet(std::string pathToJSON);
        ~SpriteSheet();
        Sprite* getSprite(std::string name, GameObject* parent);
        std::map<std::string,Material*> sprites;

    private:
        Material* findSprite(int x, int y, int width, int height, float anchorX, float anchorY);
        SRE::Texture* texture;
        SRE::Texture* normalMap = nullptr;

};
}
