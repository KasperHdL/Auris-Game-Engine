#pragma once

#include <string>
#include <map>
#include "SRE/Texture.hpp"
#include "Sprite.hpp"
#include "../../Utility/picojson.h"
#include "Material.hpp"


class SpriteSheet{

    public:
        SpriteSheet(Texture* texture,std::string pathToJSON);
        ~SpriteSheet();
        Sprite* getSprite(std::string name, GameObject* parent);
        std::map<std::string,Material*> sprites;

    private:
        
        Material* findSprite(int x, int y, int width, int height, float anchorX, float anchorY);
        SRE::Texture* texture;

};

