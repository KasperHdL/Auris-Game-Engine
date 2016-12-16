#pragma once


#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Texture.hpp"

#include "Auris/Utilities/Mesh.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Utilities/Shader.hpp"
#include "Auris/Entities/Nugget.hpp"
#include "Auris/Entities/Nuggets/Material.hpp"

#include <iostream>
namespace Auris{

//! The Sprite class that extend the Nugget class
    /*! Used to give Sprites to objects
    */
class Sprite : public Nugget{
public:
    Mesh* mesh; /*!< A Mesh pointer: mesh. The mesh of the sprite. */
    Material material; /*!< A Material value: material. The material of the sprite. */

    glm::vec3 offset = glm::vec3(0); /*!< A vec3 value: offset. The offset of the sprite (default is vec3(0)). */

    //! A draw method.
        /*!
         * Draws the sprite to the screen, with SimpleRenderEngine.
        */
    void draw();

    //! The sprite destructor.
        /*!
         * Does nothing.
        */
    ~Sprite();

    //! The overloaded sprite constructor, taking 1-4 arguments.
        /*!
         * Initializes the mesh and the material of the sprite to values inputted.
         * \param entity an Entity pointer, that is the entity the sprite is associated with.
         * \param texture a Texture pointer, that is the texture of the sprite (default is no texture).
         * \param normalMap a Texture pointer, that is the normal map of the sprite (default is no normal map).
         * \param mesh a Mesh pointer, that is the mesh of the sprite (default is no mesh).
         * \overload Sprite(Entity* entity)
        */
    Sprite(Entity* entity, SRE::Texture* texture = nullptr, SRE::Texture* normalMap = nullptr, Mesh* mesh = nullptr):Nugget(entity){
        if(mesh == nullptr)
            this->mesh = Mesh::createQuad();
        else
            this->mesh = mesh;

        if(texture == nullptr)
            material.texture = SRE::Texture::getWhiteTexture();
        else
            material.texture = texture;

        material.normalMap = normalMap;
        material.color = glm::vec4(1);

        if(normalMap == nullptr)
            material.shader = (Shader*) Shader::getUnlitSprite();
        else
            material.shader = (Shader*) Shader::getLitSprite();

    }

    //! The overloaded sprite constructor, taking 1-3 arguments.
        /*!
         * Initializes the mesh and the material of the sprite to values inputted.
         * \param entity an Entity pointer, that is the entity the sprite is associated with.
         * \param texture a Texture pointer, that is the texture of the sprite (default is no texture).
         * \param mesh a Mesh pointer, that is the mesh of the sprite (default is no mesh).
         * \overload Sprite(Entity* entity)
        */
    Sprite(Entity* entity, SRE::Texture* texture, Mesh* mesh = nullptr):Nugget(entity){
        Sprite(entity, texture, nullptr, mesh);
    }

    //! A getWidth method
    /*! Used to get the width of the currently assigned mesh in pixels
     * \return float, that is the width of the currently assigned mesh in pixels
     */
    float getWidth(){
        return mesh->width;
    }

    //! A getHeight method
    /*! Used to get the height of the currently assigned mesh in pixels
     * \return float, that is the height of the currently assigned mesh in pixels
     */
    float getHeight(){
        return mesh->height;
    }
};
}
