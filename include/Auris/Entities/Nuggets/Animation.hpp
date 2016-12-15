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

using namespace SRE;

namespace Auris{

//! The Animation class that extend the Nugget class
    /*! Used to make sprite animations
    */
class Animation : public Nugget {
public:

    std::vector<Mesh*> meshes; /*!< A vector of Mesh pointer: meshes. Reference to all the meshes in the animation. */

    //! The Animation destructor.
        /*! Clears all the meshes associated with the animation
        */
    ~Animation();

    //! The Animation contructor taking 2 arguments.
        /*! Which saves the length of the animation and also have a reference to the entity it is associated with
          \param entity an Entity pointer, that is a reference to the entity the animation is associated with.
          \param height an interger, that is the height of the window.
        */
    Animation(Entity* entity, float length);

    void addMesh(Mesh* mesh);
    void setSheet(SpriteSheet* spritesheet);
    void makeSequence(SpriteSheet* spritesheet, std::string name);
    void run(Sprite* sprite, float dt);

private:
	float length;
	float frameLength;
	float time;
	int index;
};
}
