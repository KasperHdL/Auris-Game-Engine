#pragma once

#include "glm/glm.hpp"
#include "Box2D/Box2D.h"

namespace Auris{

//! A Convert namespace
    /*! Used for converting between glm and box2D
     * vec2 to b2Vec2 and vice versa
    */
namespace Convert{

//! An inline toGlm method, taking 1 arguments.
    /*! Converts from b2Vec to vec2
     * \param v a constant b2Vec2 pointer. The b2Vec2 value to be converted to vec2.
     * \return vec2. The vec2 that the b2Vec2 has been converted to.
    */
    inline glm::vec2 toGlm(const b2Vec2 &v) {
            return glm::vec2(v.x, v.y);
    }

    //! An inline toB2 method, taking 1 arguments.
        /*! Converts from vec2 to b2Vec2
         * \param v a constant vec2 value. The vec2 value to be converted to b2Vec2.
         * \return b2Vec2. The b2Vec2 that the vec2 has been converted to.
        */
    inline b2Vec2 toB2(const glm::vec2 v){
        return b2Vec2(v.x,v.y);
    }
}
}
