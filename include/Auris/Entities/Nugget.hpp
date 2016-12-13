#pragma once

namespace Auris{
class Entity;

class Nugget {
    public:
        Nugget(Entity* entity):entity(entity){};
        virtual ~Nugget(){
            entity = nullptr;
        };

        Entity* entity;
        friend class entity;

};

}
