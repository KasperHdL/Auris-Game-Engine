#pragma once

#include "SRE/Texture.hpp"
#include "SRE/Mesh.hpp"
#include "glm/glm.hpp"

namespace Auris{
class Material{
private:
    SRE::Texture* texture;
    SRE::Texture* normalMap;
    glm::vec4 color;
    SRE::Mesh* mesh;
public:
    ~Material() {
        delete mesh;
        mesh = nullptr;
    }

    void setTexture(SRE::Texture* texture = SRE::Texture::getWhiteTexture()){
        if(texture==nullptr){
            this->texture = SRE::Texture::getWhiteTexture();
        }else{
            this->texture = texture;
        }
    }

    void setNormalMap(SRE::Texture* normalMap = nullptr){
        this->normalMap = normalMap;
    }

    void setColor(glm::vec4 color = glm::vec4(1)){
        this->color = color;
    }
    void setMesh(SRE::Mesh* mesh=SRE::Mesh::createCube()){
        if(mesh==nullptr){
            this->mesh = SRE::Mesh::createCube();
        }else{
            this->mesh = mesh;
        }

    }

    SRE::Texture* getTexture(){
        return texture;
    }

    SRE::Texture* getNormalMap(){
        return normalMap;
    }

    glm::vec4 getColor(){
        return color;
    }

    SRE::Mesh* getMesh(){
        return mesh;
    }
};
}
