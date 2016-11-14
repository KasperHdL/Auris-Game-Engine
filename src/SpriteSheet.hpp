#pragma once

#include <string>
#include <map>
#include "SRE/Texture.hpp"
#include "src/GameObjects/Components/Sprite.hpp"
#include "picojson.h"


class SpriteSheet{

    public:
        
        SpriteSheet(Texture* texture,std::string pathToJSON, GameObject* go);
        ~SpriteSheet();
        Sprite* getSprite(std::string name);

    private:
        
        Sprite* findSprite(int x, int y, int width, int height, float anchorX, float anchorY);
        std::map<std::string,Sprite*> sprites;
        SRE::Texture* texture;
        GameObject* parent;

};

