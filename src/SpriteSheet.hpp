#pragma once

#include <string>
#include <map>
#include "SRE/Texture.hpp"
#include "src/GameObjects/Components/Sprite.hpp"
#include "picojson.h"
#include "Material.hpp"


class SpriteSheet{

    public:
        
        SpriteSheet(Texture* texture,std::string pathToJSON);
        ~SpriteSheet();
        Sprite* getSprite(std::string name, GameObject* parent);

    private:
        
        Material* findSprite(int x, int y, int width, int height, float anchorX, float anchorY);
        std::map<std::string,Material*> sprites;
        SRE::Texture* texture;

};

