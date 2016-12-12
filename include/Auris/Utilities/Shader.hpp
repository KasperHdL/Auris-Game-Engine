#pragma once

#include "SRE/Shader.hpp"

namespace Auris{
class Shader : public SRE::Shader{
    public:
        static SRE::Shader* getLitSprite();
    
    private:
        static SRE::Shader* litSprite;


};
}
