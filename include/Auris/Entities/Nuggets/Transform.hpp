#pragma once
#include "Auris/Entities/Nugget.hpp"
#include "Auris/Constants.hpp"

#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Auris{
using namespace glm;

//! The Transform class that extend the Nugget class
    /*! Used as the transform of objects
    */
class Transform : public Nugget{
    public:
        vec3 position; /*!< A vec3 value: position. The position of the transform. */
        vec2 scale;/*!< A vec2 value: scale. The scale of the transform. */
        float rotation; /*!< A float value: rotation. The rotation of the transform. */


        //! The Transform constructor, taking 1 argument.
            /*!
             * Initializes the position, scale and rotation of the transform to default values.
             * \param entity an Entity pointer, that is the entity the transform is associated with.
            */
        Transform(Entity* entity):Nugget(entity){
            position = vec3(0,0,0);
            scale = vec2(1,1);
            rotation = 0;
        
        }

        //! A getLocal method, taking 0-1 argument.
            /*!
             * Gets the local matrix of the transform
             * \param offset an vec3 value, that is the offset of the local transform (default is vec3(0)).
             * \return mat4, that is the matrix of the local transform
            */
        mat4 getLocal(vec3 offset = vec3(0));

        //! A getGlobal method, taking 0-1 argument.
            /*!
             * Gets the global matrix of the transform from the local
             * \param offset an vec3 value, that is the offset of the global transform (default is vec3(0)).
             * \return mat4, that is the matrix of the global transform
            */
        mat4 getGlobal(vec3 offset = vec3(0));
        
        //! A getGlobalPosition method
            /*!
             * Gets the global position of the transform
             * \return vec3, that is the position of the global transform
            */
        vec3 getGlobalPosition();


};
}
