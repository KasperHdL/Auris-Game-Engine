#include "Auris/Utilities/AssetManager.hpp"

namespace Auris{

std::map<std::string, SRE::Texture*> AssetManager::textures;
std::map<std::string, SpriteSheet*> AssetManager::spritesheets;

std::map<std::string, Mix_Music*> AssetManager::music;
std::map<std::string, Mix_Chunk*> AssetManager::sounds;

/////////
// Get

//! Load texture file and creates Texture and returns pointer to Texture, the pointer must NOT be deleted this will be handled by the AssetManager or you can manually call freeTexture
/*!
 * \param filename filename of the .png or .jpeg file in the data folder
 * \return SRE::Texture* pointer to the Texture (DO NOT DELETE)
 */
SRE::Texture* AssetManager::getTexture(std::string filename, bool filterSampling){
    if(AssetManager::textures[filename] == nullptr){
        AssetManager::textures[filename] = SRE::Texture::createFromFile(getDataPath(filename).c_str(), false);
        AssetManager::textures[filename]->setFilterSampling(filterSampling);
    }
    return AssetManager::textures[filename];
}


//! Load json file and creates spritesheet and returns pointer to SpriteSheet, the pointer must NOT be deleted this will be handled by the AssetManager or you can manually call freeSpriteSheet
/*!
 * \param filename filename of the .json file in the data folder
 * \return SpriteSheet* pointer to the SpriteSheet  (DO NOT DELETE)
 */
SpriteSheet* AssetManager::getSpriteSheet(std::string jsonFilename, bool createFlipped, bool filterSampling){
    if(AssetManager::spritesheets[jsonFilename] == nullptr){

        AssetManager::spritesheets[jsonFilename] = new SpriteSheet();
        AssetManager::createSheet(AssetManager::spritesheets[jsonFilename], jsonFilename, createFlipped, filterSampling);
        
    }
    return AssetManager::spritesheets[jsonFilename];

}

//! Load file and return pointer to Mix_Music, the pointer must NOT be deleted this will be handled by the AssetManager or call freeMusic
/*!
 * \param filename filename of the .wav file in the data folder
 * \return Mix_Music* pointer to Mix_Music* to be passed to a AudioPlayer(DO NOT DELETE)
 * \sa AudioPlayer.addMusic()
 * \sa getSound()
 */
Mix_Music* AssetManager::getMusic(std::string filename) {
    if(AssetManager::music[filename] == nullptr){
        AssetManager::music[filename] = Mix_LoadMUS(AssetManager::getDataPath(filename).c_str());
        if (AssetManager::music[filename] == nullptr) {
            std::cout << "Nullptr: Failed to load Music \"" << filename << "\". Make sure the filename is correct and that the file is placed in the data folder." << std::endl;
            return nullptr;
        }
    }
    return AssetManager::music[filename];
}

//! Load file and get pointer to Mix_Chunk*, the pointer must NOT be deleted this will be handled by the AssetManager or call freeSound
/*!
 * \param filename filename of the .wav file in the data folder
 * \return Mix_Chunk* pointer to Mix_Chunk* to be passed to AudioPlayer (DO NOT DELETE)
 * \sa AudioPlayer.addSound()
 * \sa getMusic()
 */
Mix_Chunk* AssetManager::getSound(std::string filename) {

    if(AssetManager::sounds[filename] == nullptr){
        AssetManager::sounds[filename] = Mix_LoadWAV(AssetManager::getDataPath(filename).c_str());
        if (AssetManager::sounds[filename] == nullptr) {
            std::cout << "Nullptr: Failed to load Sound \"" << filename << "\". Make sure the filename is correct and that the file is placed in the data folder." << std::endl;
            return nullptr;
        }
    }
    return AssetManager::sounds[filename];
}

/////////
// Free 


///////////////////
// Private Methods
///////////////////

void AssetManager::createSheet(SpriteSheet* sheet, std::string jsonFilename, bool createFlipped, bool filterSampling){

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
                sheet->texture = getTexture(stuff.second.get<std::string>(), filterSampling);
            }if(stuff.first=="normal"){
                sheet->normalMap = getTexture(stuff.second.get<std::string>(), filterSampling);
            }
        }

        for(auto & element : arr){

            for(int flip = 0;flip < (createFlipped ? 2:1);flip++){
                
                int x = (int)element.get("frame").get("x").get<double>();
                int y = (int)element.get("frame").get("y").get<double>();
                int width = (int)element.get("frame").get("w").get<double>();
                int height = (int)element.get("frame").get("h").get<double>();
                float ax = (float)element.get("pivot").get("x").get<double>();
                float ay = (float)element.get("pivot").get("y").get<double>();
                std::string name = element.get("filename").get<std::string>();

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

                if(flip == 0)
                    sheet->meshes[name] = new Mesh(vertices, normals, uvs, width, height);
                else
                    sheet->meshes["flipped_" + name] = new Mesh(vertices, normals, {uvs[2],uvs[5],uvs[0],uvs[0],uvs[5],uvs[1]}, width, height);
            }
        }

}


}
