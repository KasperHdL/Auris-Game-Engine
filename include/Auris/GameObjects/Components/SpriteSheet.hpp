#pragma once

#include <string>
#include <map>
#include "SRE/Texture.hpp"

#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/Utility/picojson.h"
#include "Auris/GameObjects/Components/Material.hpp"


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

