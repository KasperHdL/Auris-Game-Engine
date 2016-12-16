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

        //! A getSprite method, taking 2 arguments.
            /*! Creates a sprite from the render system with the spritesheet, and gives it back
             * \param name a String value, that is the name of the sprite
             * \param parent an Entity pointer, that is the entity that is associated with the sprite
             * \return Sprite pointer, that is the sprite created
            */
        Sprite* getSprite(std::string name, Entity* parent);

        std::map<std::string, Auris::Mesh*> meshes; /*!< A map of strings and mesh pointer pointer: meshes. Reference to the mesh, dependent on the string. */
        SRE::Texture* texture; /*!< A Texture pointer: texture. Reference to the texture of the sprite. */
        SRE::Texture* normalMap = nullptr; /*!< A Texture pointer: normalMap. Reference to the normal map of the sprite (default is no normal map). */

};
}
