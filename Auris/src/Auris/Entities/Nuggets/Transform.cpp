#include "Auris/Entities/Nuggets/Transform.hpp"
#include "Auris/Entity.hpp"

namespace Auris{

    glm::mat4 Transform::getLocal(vec3 offset) {
        if(!dirty && lastOffset == offset) return localTransform;
        lastOffset = offset;

        mat4 rz = glm::eulerAngleZ(rotation);
        mat4 t = glm::translate(glm::mat4(1), (offset + position) * Constants::METERS_TO_PIXELS);
        mat4 s = glm::scale(glm::mat4(1), vec3(scale, 1));

        localTransform = t * rz * s;
        dirty = false;
        return localTransform;
    }

    glm::mat4 Transform::getGlobal(vec3 offset) {

        if(entity->parent == nullptr)
            return getLocal(offset);
        
        return entity->parent->transform->getGlobal() * getLocal(offset);
    }

    glm::vec3 Transform::getGlobalPosition(){
        if(entity->parent == nullptr)
            return position;

        return entity->parent->transform->getGlobalPosition() + position;
    }




}
