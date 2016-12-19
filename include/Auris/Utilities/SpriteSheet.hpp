#pragma once

#include <string>
#include <map>
#include "SRE/Texture.hpp"
#include "Auris/Utilities/Mesh.hpp"

#include "Auris/Entities/Nuggets/Sprite.hpp"


namespace Auris{

//! The Spritesheet class
    /*! Used to make spritesheets
    */
class SpriteSheet{
    public:

        //! The Spritesheet constructor.
           /*! Does nothing
            */
        SpriteSheet();

        //! The Spritesheet destructor.
            /*! Clear all meshes, textures and normal maps
            */
        ~SpriteSheet();

        //! A setSpriteTo method, taking 2 arguments. The Sprite passed must be initialized \sa RenderSystem::getSprite()
            /*! Sets the sprite mesh to the one corresponding with the name given, if name does not exist then it prints an error
             * \param sprite an Sprite pointer, which mesh will change to correspond with the given name of the spritesheet frame 
             * \param name a String value, that is the name of the sprite
             * \param getFlipped a bool value. Set the sprite to be flipped or not
             * \sa RenderSystem::getSprite()
            */
        void setSpriteTo(Sprite* sprite, std::string name, bool getFlipped = false);

        std::map<std::string, Auris::Mesh*> meshes; /*!< A map of strings and Mesh pointer pointer: meshes. Reference to the Mesh, dependent on the string. */
        SRE::Texture* texture; /*!< A Texture pointer: texture. Reference to the Texture of the sprite. */
        SRE::Texture* normalMap = nullptr; /*!< A Texture pointer: normalMap. Reference to the normal map of the sprite (default is no normal map). */

};
}
