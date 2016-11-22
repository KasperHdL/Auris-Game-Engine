#pragma once

#include "glm/glm.hpp"
#include "Box2D/Box2D.h"

namespace Convert{
    glm::vec2 vector(const b2Vec2& v){
        return glm::vec2(v.x,v.y);
    }

    b2Vec2 vector(const glm::vec2& v){
        return b2Vec2(v.x,v.y);
    }
}
