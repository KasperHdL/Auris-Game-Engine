#include "Auris/Utilities/AssetManager.hpp"

namespace Auris{

std::map<std::string, SRE::Texture*> AssetManager::textures;
std::map<std::string, SpriteSheet*> AssetManager::spritesheets;

SRE::Texture* AssetManager::getTexture(std::string filename){
    if(AssetManager::textures[filename] == nullptr){
        AssetManager::textures[filename] = SRE::Texture::createFromFile(getDataPath(filename).c_str(), false);
    }
    return AssetManager::textures[filename];
}

SpriteSheet* AssetManager::getSpriteSheet(std::string jsonFilename){
    if(AssetManager::spritesheets[jsonFilename] == nullptr){

        AssetManager::spritesheets[jsonFilename] = new SpriteSheet();
        AssetManager::createSheet(AssetManager::spritesheets[jsonFilename], jsonFilename);
        
    }
    return AssetManager::spritesheets[jsonFilename];

}


///////////////////
// Private Methods
///////////////////

void AssetManager::createSheet(SpriteSheet* sheet, std::string jsonFilename){

        bool invertY = true;

        picojson::value v;
        std::ifstream t(AssetManager::getDataPath(jsonFilename).c_str());
        t >> v;
        std::string err = picojson::get_last_error();
        if(err != ""){
            std::cerr << err << std::endl;
        }

        picojson::array arr = v.get("frames").get<picojson::array>();
        picojson::value::object meta = v.get("meta").get<picojson::value::object>();

        for(auto & stuff : meta){
            if(stuff.first=="image"){
                sheet->texture = getTexture(stuff.second.get<std::string>());
            }if(stuff.first=="normal"){
                sheet->normalMap = getTexture(stuff.second.get<std::string>());
            }
        }

        for(auto & element : arr){

            int x = (int)element.get("frame").get("x").get<double>();
            int y = (int)element.get("frame").get("y").get<double>();
            int width = (int)element.get("frame").get("w").get<double>();
            int height = (int)element.get("frame").get("h").get<double>();
            float ax = (float)element.get("pivot").get("x").get<double>();
            float ay = (float)element.get("pivot").get("y").get<double>();
            std::string name = element.get("filename").get<std::string>();

            //@TODO should have a paranthesis
            y = sheet->texture->getHeight() - height - y;

            float offsetX = (float)-width * ax;
            float offsetY = (float)-height * ay;

            std::vector<glm::vec3> vertices({
                    glm::vec3{ width + offsetX, offsetY, 0 }, 
                    glm::vec3{ width + offsetX, height + offsetY, 0 },
                    glm::vec3{ offsetX, offsetY, 0 },

                    glm::vec3{ offsetX, offsetY, 0 }, 
                    glm::vec3{ width + offsetX, height + offsetY, 0 }, 
                    glm::vec3{ offsetX, height + offsetY, 0 }
                });

            // Per pixel normals are used for 2D graphics, but the mesh still needs an empty normal vector
            std::vector<glm::vec3> normals;

            // UVs contains the normalized texture coordinates.
            float uvx1 = (float)x / sheet->texture->getWidth();
            float uvy1 = (float)y / sheet->texture->getHeight();
            float uvx2 = ((float)(x + width)) / sheet->texture->getWidth();
            float uvy2 = ((float)(y + height)) / sheet->texture->getHeight();

            std::vector<glm::vec2> uvs({
                glm::vec2{ uvx2, uvy1 }, glm::vec2{ uvx2, uvy2 }, glm::vec2{ uvx1, uvy1 },
                glm::vec2{ uvx1, uvy1 }, glm::vec2{ uvx2, uvy2 }, glm::vec2{ uvx1, uvy2 }
            });

            sheet->meshes[name] = new Mesh(vertices, normals, uvs, width, height);
        }

}


}
