#pragma once


#include "Auris/Entity.hpp"

using namespace Auris;
class Char : public Entity{

    Char(vec2 position, bool withTexture = true, bool withNormalMap = true, bool withAnimation= true):Entity(){
        name = "Entity";
        type = "Character";

        if(withTexture){

        }



    }

};
