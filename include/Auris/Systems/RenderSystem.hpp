#pragma once

#include <vector>
#include <memory>

#include "Auris/Entity.hpp"
#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Entities/Nuggets/Animation.hpp"
#include "Auris/Utilities/DynamicPool.hpp"

#include "Auris/Utilities/Mesh.hpp"
#include "SRE/Texture.hpp"

namespace Auris{
using namespace std;

//! The RenderSystem class
    /*! Controls all the sprites and animations
    */
class RenderSystem{

public:
    static DynamicPool<Sprite> spritePool; /*!< A Pool of Sprite values: spritePool. The pool that all sprites are within. */
    static vector<shared_ptr<Animation>> animations; /*!< A vector of shared pointer of Animation values: animations. The vector of all animations in the engine. */

    //! The RenderSystem constructor.
        /*!
         * Does nothing.
        */
    RenderSystem(){}

    //! The RenderSystem destructor.
        /*!
         * Does nothing.
        */
    ~RenderSystem(){}

    //! A startup method, taking 1 argument.
        /*!
         * Starts the rendersystem and reserve space in memeory for the sprites
         * \param reserve an int value. The amount to reserve
        */
    void startup();

    //! A shutdown method.
        /*!
         * Shuts down the rendersystem and clears the animations
        */
    void shutdown();

    //! An update method, taking 1 argument.
        /*!
         * Updates the rendersystem and draws all sprites
         * \param dt a float value. The delta time in seconds.
        */
    void update(float dt);

    //! A static getSrite method, taking 1-4 arguments.
        /*!
         * Creates a new sprite and returns it
         * \param entity an Entity pointer. The Entity that needs the sprite.
         * \param texture a Texture pointer. The texture of the sprite (default is white texture).
         * \param mesh a Mesh pointer. The mesh of the sprite (default is quad mesh).
         * \param normalMap a Texture pointer. The normal map of the the sprite (default is no normal map).
         * return Sprite. The sprite created.
        */
    static Sprite* getSprite(Entity* entity, SRE::Texture* texture = nullptr,Auris::Mesh* mesh = nullptr,SRE::Texture* normalMap = nullptr);

    //! A static deleteSprite method, taking 1 argument.
        /*!
         * Removes the sprite from the sprite pool
         * \param sprite a Sprite pointer. The Sprite to remove.
        */
    static void deleteSprite(Sprite* sprite);

    //! A static getAnim method, taking 2 arguments.
        /*!
         * Creates a new animation and returns it
         * \param entity an Entity pointer. The Entity that needs the animation.
         * \param length a float value. The length of the animation
         * return shared_ptr of Animation. A shared pointer to the animation.
        */
	static shared_ptr<Animation> getAnim(Entity* entity, float length);

    //! A static deleteAnim method, taking 1 argument.
        /*!
         * Removes the animation from the animation vector.
         * \param ani a shared_ptr of animation value. The animation to remove.
        */
    static void deleteAnim(shared_ptr<Animation> ani);
};
}
