#pragma once

#include "glm/glm.hpp"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Texture.hpp"

#include <iostream>

#include "Auris/Utilities/Mesh.hpp"
#include "Auris/Utilities/Shader.hpp"
#include "Auris/Utilities/SpriteSheet.hpp"
#include "Auris/Entity.hpp"
#include "Auris/Entities/Nuggets/Sprite.hpp"

namespace Auris{

//! The Animation class that extend the Nugget class
    /*! Used to make sprite animations
    */
class Animation : public Nugget {
public:

    std::vector<Mesh*> meshes; /*!< A vector of Mesh pointer: meshes. Reference to all the meshes in the animation. */
    std::vector<Mesh*> flipped_meshes; /*!< A vector of Mesh pointer: flipped_meshes. Reference to all the flipped meshes in the animation, makeSequence must be called with createFlipped = true \sa makeSequence()*/

    //! The Animation destructor.
        /*! Clears all the meshes associated with the animation
        */
    ~Animation();

    //! The Animation contructor, taking 2 arguments.
        /*! Which saves the length of the animation and also have a reference to the entity it is associated with
          \param entity an Entity pointer, that is a reference to the entity the animation is associated with.
          \param height an interger, that is the height of the window.
        */
    Animation(Entity* entity, float length);

    //! The method addMesh, taking 1 argument.
        /*!
         * Adds a mesh to the vector of all meshes
         * \param mesh a Mesh pointer, that is the mesh to add
        */
    void addMesh(Mesh* mesh);

    //! The method setSheet, taking 1 argument.
        /*!
         * Set the spritesheet of the animation
         * \param spritesheet a SpriteSheet pointer, that is the spritesheet to add
        */
    void setSheet(SpriteSheet* spritesheet);

    //! The method makeSequence, taking 2 arguments.
        /*!
         * Make the animation use a sequence of sprites in a spritesheet
         * \param spritesheet a SpriteSheet pointer. The spritesheet to add
         * \param name a string. The name of the sequence in the spritesheet
        */
    void makeSequence(SpriteSheet* spritesheet, std::string name, bool createFlipped = false);

    //! The method run, taking 2 arguments.
        /*! Makes the animation execute
         * \param sprite a Sprite pointer, that is the sprite to add the animation to
         * \param dt a float, that is the delta time
        */
    void run(Sprite* sprite, float dt, bool getFlipped = false);

private:
    float length; /*!< A float value: length. The length of the animation. */
    float frameLength; /*!< A float value: frameLength. The length of each frame. */
    float time; /*!< A float value: time. The current animation time. */
    int index; /*!< An int value: index. The index of the current frame. */
};
}
