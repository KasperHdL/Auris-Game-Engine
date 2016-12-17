#include "Auris/Entities/PhysicsEntity.hpp"

namespace Auris{
    PhysicsEntity::~PhysicsEntity(){
        Engine::instance->world->DestroyBody(body);
    }
}
