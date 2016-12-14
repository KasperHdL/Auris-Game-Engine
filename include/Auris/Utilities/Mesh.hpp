#pragma once

#include "SRE/Mesh.hpp"
namespace Auris{
class Mesh : public SRE::Mesh{
    public:
        Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, float width, float height):SRE::Mesh(vertices, normals, uvs), width(width), height(height){}
        float width = 1;
        float height = 1;

        static Mesh* createCube(){
            return (Mesh*) SRE::Mesh::createCube();
        }

        static Mesh* createSphere(){
            return (Mesh*) SRE::Mesh::createSphere();
        }

        static Mesh* createQuad(){
            return (Mesh*) SRE::Mesh::createQuad();
        }


};
}
