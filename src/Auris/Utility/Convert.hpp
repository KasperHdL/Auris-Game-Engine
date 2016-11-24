#pragma once

#include "glm/glm.hpp"
#include "Box2D/Box2D.h"

namespace Convert{
    inline glm::vec2 toGlm(const b2Vec2 &v) {
            return glm::vec2(v.x, v.y);
    }
    inline b2Vec2 toB2(const glm::vec2 v){
        return b2Vec2(v.x,v.y);
    }
}
