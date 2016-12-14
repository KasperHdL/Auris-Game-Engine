#include "Auris/Entities/Nuggets/SpriteSheet.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include <fstream>
#include <iostream>

#include "Auris/Utilities/AssetManager.hpp"

using namespace Auris;
using namespace std;
SpriteSheet::SpriteSheet(string pathToJSON){

    //SpriteSheet::texture = texture;
    bool invertY = true;

    picojson::value v;
    ifstream t(pathToJSON);
    t >> v;
    string err = picojson::get_last_error();
    if(err != ""){
        cerr<<err<<endl;
    }
    picojson::array arr = v.get("frames").get<picojson::array>();
    picojson::value::object meta = v.get("meta").get<picojson::value::object>();

    for(auto & stuff : meta){
        if(stuff.first=="image"){
            texture = AssetManager(stuff.second.get<string>());
        }if(stuff.first=="normal"){
            normalMap = AssetManager(stuff.second.get<string>());
        }
    }
    //cout << meta.get("image").get<string>; << endl;
    for(auto & element : arr){

        int x = (int)element.get("frame").get("x").get<double>();
        int y = (int)element.get("frame").get("y").get<double>();
        int width = (int)element.get("frame").get("w").get<double>();
        int height = (int)element.get("frame").get("h").get<double>();
        float ax = (float)element.get("pivot").get("x").get<double>();
        float ay = (float)element.get("pivot").get("y").get<double>();
        string name = element.get("filename").get<std::string>();

        addMesh(name, x, texture->getHeight()-height-y, width, height, ax, ay);
    }
}

Auris::Mesh* SpriteSheet::addMesh(string name, int x, int y, int width, int height, float anchorX, float anchorY){
    float offsetX = (float)-width * anchorX;
    float offsetY = (float)-height * anchorY;

//    cout << anchorX << " : " << anchorY << endl;
//    cout << offsetX << " : " << offsetY << endl;
//    cout << width << " : " << height << endl;

    std::vector<glm::vec3> vertices({
            glm::vec3{ width + offsetX, offsetY, 0 }, glm::vec3{ width + offsetX, height + offsetY, 0 },glm::vec3{ offsetX, offsetY, 0 },
            glm::vec3{ offsetX, offsetY, 0 }, glm::vec3{ width + offsetX, height + offsetY, 0 }, glm::vec3{ offsetX, height + offsetY, 0 }
        });

    // Normals are not used for 2D graphics
    std::vector<glm::vec3> normals;

    // UVs containts the normalized texture coordinates.
    float uvx1 = (float)x / SpriteSheet::texture->getWidth();
    float uvy1 = (float)y / SpriteSheet::texture->getHeight();
    float uvx2 = ((float)(x + width)) / SpriteSheet::texture->getWidth();
    float uvy2 = ((float)(y + height)) / SpriteSheet::texture->getHeight();

    std::vector<glm::vec2> uvs({
        glm::vec2{ uvx2, uvy1 }, glm::vec2{ uvx2, uvy2 }, glm::vec2{ uvx1, uvy1 },
        glm::vec2{ uvx1, uvy1 }, glm::vec2{ uvx2, uvy2 }, glm::vec2{ uvx1, uvy2 }
    });

    meshes[name] = new Mesh(vertices, normals, uvs, width, height);
    return meshes[name];

}

SpriteSheet::~SpriteSheet(){

    for(map<std::string, Auris::Mesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it){
        delete it->second;
        it->second = nullptr;
    }

    meshes.clear();
    delete texture;
    texture = nullptr;
}

Sprite* SpriteSheet::getSprite(string name, Entity* parent){
    auto s = RenderSystem::getSprite(parent, meshes[name], texture, normalMap);
    return s;
}

