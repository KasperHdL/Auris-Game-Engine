#pragma once

#include "SRE/Mesh.hpp"
namespace Auris{

//! The Mesh class that extend the SRE::Mesh class
    /*! Used to manipulate meshes.
    */
class Mesh : public SRE::Mesh{
    public:

    //! The mesh contructor, taking 5 arguments.
        /*! Initializes a mesh with the input arguments in SRE::Mesh.
         * \param vectices a vector of vec3. The vectives of the mesh.
         * \param normals a vector of vec3. The normals of the mesh.
         * \param uvs a vector of vec3. The uvs of the mesh.
         * \param width a float value. The width of the mesh.
         * \param height a float value. The height of the mesh.
        */
        Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, float width, float height):SRE::Mesh(vertices, normals, uvs), width(width), height(height){}
        float width = 1; /*!< A float value: width. The width of the mesh. */
        float height = 1; /*!< A float value: height. The height of the mesh. */

        //! A createCube method.
            /*! Creates a cube from SRE::Mesh and returns it.
             * \return Mesh pointer. The mesh created.
            */
        static Mesh* createCube(){
            return (Mesh*) SRE::Mesh::createCube();
        }

        //! A createSphere method.
            /*! Creates a sphere from SRE::Mesh and returns it.
             * \return Mesh pointer. The mesh created.
            */
        static Mesh* createSphere(){
            return (Mesh*) SRE::Mesh::createSphere();
        }

        //! A createQuad method.
            /*! Creates a quad from SRE::Mesh and returns it.
             * \return Mesh pointer. The mesh created.
            */
        static Mesh* createQuad(){
            return (Mesh*) SRE::Mesh::createQuad();
        }


};
}
