#pragma once

#include "SRE/Shader.hpp"

namespace Auris{

//! The Shader class that extend the SRE::Shader class
    /*! Used to manipulate shader.
    */
class Shader : public SRE::Shader{
    public:

    //! A static getLitSprite method.
        /*! Creates a lit sprite shader via the SRE::Shader::CreateShader() method and returns it.
         * \return Shader pointer. The shader created.
         * \sa SRE::Shader::CreateShader()
        */
        static Shader* getLitSprite();

        //! A static getUnlitSprite method.
            /*! Creates a Unlit sprite shader from the SRE::Shader::getUnlitSprite() method and returns it.
             * \return Shader pointer. The shader created.
             * \sa SRE::Shader::getUnlitSprite()
            */
        static Shader* getUnlitSprite(){
            return (Shader*) SRE::Shader::getUnlitSprite();
        }
 
        //! A static getStandardParticles method.
            /*! Creates a standard particle shader from the SRE::Shader::getStandardParticles method and returns it.
             * \return Shader pointer. The shader created.
             * \sa SRE::Shader::getStandardParticles()
            */
        static Shader* getStandardParticles(){
            return (Shader*) SRE::Shader::getStandardParticles();
        }
   
    private:
        static SRE::Shader* litSprite; /*!< A Shader pointer: litSprite. Hold an instance of the lit sprite shader. */

};
}
