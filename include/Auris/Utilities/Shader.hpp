#pragma once

#include "SRE/Shader.hpp"

namespace Auris{
class Shader : public SRE::Shader{
    public:
        static Shader* getLitSprite();

        static Shader* getUnlitSprite(){
            return (Shader*) SRE::Shader::getUnlitSprite();
        }
 
        static Shader* getStandardParticles(){
            return (Shader*) SRE::Shader::getStandardParticles();
        }
   
    private:
        static SRE::Shader* litSprite;

};
}
