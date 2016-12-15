#pragma once

namespace Auris{
class Entity;

//! The Nugget class
    /*! Nuggets are sort of the components of the system.
     * Every other nugget inherents from this base nugget
    */
class Nugget {
    public:

    //! The nugget contructor taking 1 arguments.
        /*!
          \param entity an Entity. A reference to the Entity the nugget is associated with.
        */
        Nugget(Entity* entity):entity(entity){}

        //! The nugget destructor.
            /*! The destructor null points the Entity pointer, can be overwritten by the nuggets that inherents from this
            */
        virtual ~Nugget(){
            entity = nullptr;
        }

        Entity* entity; /*!< A Entity pointer: entity. A reference to the Entity that the nugget is associated with */
        friend class entity;

};

}
