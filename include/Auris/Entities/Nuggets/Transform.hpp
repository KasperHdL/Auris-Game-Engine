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


        //! A getGlobalPosition method
            /*!
             * Gets the global position of the transform, reduce the amount of getGlobalPosition calls, since it will traverse the hierarchy and get matrix transforms for parent recursively
             * \return vec3, that is the position of the global transform
            */
        vec3 getGlobalPosition();

        //! Getter for position
            /*!
             * Get the local position as a vector2
             * \return vec2, position
             * \sa getGlobalPosition()
             * \sa getPositionVec3()
             * \sa getZ()
            */
        vec2 getPosition(){return position;}
 
        //! Getter for position as a vector3
            /*!
             * Get the position as a vector3
             * \return vec3, position
             * \sa getGlobalPosition()
             * \sa getPosition()
             * \sa getZ()
            */
        vec3 getPositionVec3(){return position;}

        //! Getter for Z of the position
            /*!
             * Get the z position as a float
             * \return float, z of the position
             * \sa getPosition()
             * \sa getPositionVec3()
             * \sa getGlobalPosition()
             */
        float getZ(){return position.z;}

        //! Add to the position
            /*!
             * Add the value to the position
             * \param a vec2 value, the amount to be added to the position
             * \overload addToPosition(vec3 value)
             */
        void addToPosition(vec2 value){addToPosition(vec3(value,0));}

        //! Add to the position
            /*!
             * Add the value to the position
             * \param a vec3 value, the amount to be added to the position
             * \overload addToPosition(vec2 value)
             */
        void addToPosition(vec3 value){
            dirty = true;
            position += value;
        }

        //! Setter for the position
            /*!
             * Set the position with a vec2 value
             * \param a vec2 value, the new position (the z value if set will remain the same)
             * \overload setPosition(vec3 value)
             */
        void setPosition(vec2 value){setPosition(vec3(value,position.z));}

        //! Setter for the position
            /*!
             * Set the position with a vec3 value
             * \param a vec3 value, the new position
             * \overload setPosition(vec3 value)
             */
        void setPosition(vec3 value){
            dirty = true;
            position = value;
        }

        //! add to scale
            /*!
             * add an vec2 to the scale
             * \param a vec2 value, the amount to add to scale
             * \sa setScale(vec2 value)
             */
        void addToScale(vec2 value){
            dirty = true;
            scale += value;
        }

        //! set scale
            /*!
             * set scale to the given value
             * \param a vec2 value, the value to set scale
             * \overload setScale(float value)
             * \sa addToScale(vec2 value)
             */
        void setScale(vec2 value){
            dirty = true;
            scale = value;
        }

        //! set scale
            /*!
             * set scale to the given value in both x and y
             * \param a float value, the value to set scale in both axis
             * \overload setScale(vec2 value)
             */
        void setScale(float value){
            dirty = true;
            scale = vec2(value,value);
        }

        //! Getter for scale
            /*!
             * get scale
             * \return a vec2 value, the scale
             * \sa setScale(vec2 value)
             */
        vec2 getScale(){return scale;}

        //! add to rotation
            /*!
             * add an float to the rotation
             * \param float value, the amount to add to rotation
             * \sa setRotation(float value)
             * \sa getRotation()
             */
        void addToRotation(float value){
            dirty = true;
            rotation += value;
        }

        //! set rotation
            /*!
             * set the rotation of the transform
             * \param float value, the value to set rotation to
             * \sa addToRotation(float value)
             * \sa getRotation()
             */
        void setRotation(float value){
            dirty = true;
            rotation = value;
        }

        //! get rotation
            /*!
             * \brief getter for rotation of the transform
             * \return An float value, the rotation of the transform
             */
        float getRotation(){return rotation;}

       //! The Transform constructor, taking 1 argument.
            /*!
             * Initializes the position, scale and rotation of the transform to default values.
             * \param entity an Entity pointer, that is the entity the transform is associated with.
            */
        Transform(Entity* entity):Nugget(entity){
            position = vec3(0,0,0);
            scale = vec2(1,1);
            rotation = 0;
            dirty = true;
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

    private:
        bool dirty = true;//!< a bool value: dirty. whether or not it will recalculate global-local transforms when getLocal or getGlobal is called

        vec3 position; /*!< A vec3 value: position. The position of the transform. */
        vec2 scale;/*!< A vec2 value: scale. The scale of the transform. */
        float rotation; /*!< A float value: rotation. The rotation of the transform. */

        mat4 localTransform;//!< A mat4 value localTransform, for optimization caching
        vec3 lastOffset;
};
}
