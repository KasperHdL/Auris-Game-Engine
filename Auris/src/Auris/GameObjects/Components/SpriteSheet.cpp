#include "SpriteSheet.hpp"
#include "../../Systems/RenderSystem.hpp"
#include <fstream>

using namespace std;
SpriteSheet::SpriteSheet(Texture* texture,string pathToJSON){

    SpriteSheet::texture = texture;

    picojson::value v;
    ifstream t(pathToJSON);
    t >> v;
    string err = picojson::get_last_error();
    if(err != ""){
        cerr<<err<<endl;
    }
    picojson::array arr = v.get("frames").get<picojson::array>();
    for(auto & element : arr){

        int x = (int)element.get("frame").get("x").get<double>();
        int y = (int)element.get("frame").get("y").get<double>();
        int width = (int)element.get("frame").get("w").get<double>();
        int height = (int)element.get("frame").get("h").get<double>();
        float ax = (float)element.get("pivot").get("x").get<double>();
        float ay = (float)element.get("pivot").get("y").get<double>();

        SpriteSheet::sprites[element.get("filename").get<std::string>()] = findSprite(x,texture->getHeight()-height-y,width,height,ax,ay);
    }
}

Material* SpriteSheet::findSprite(int x, int y, int width, int height, float anchorX, float anchorY){
    float offsetX = (float)width*-0.5f;
    float offsetY = (float)height*-0.5f;

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

        Material* mat = new Material();
        mat->mesh = new SRE::Mesh(vertices, normals, uvs);
        //mat->mesh = Mesh::createCube();
        mat->texture = SpriteSheet::texture;

        //as of now only white (fixed!)
        mat->color = glm::vec4(1,1,1,1);

        return mat;


}

SpriteSheet::~SpriteSheet(){
    sprites.clear();
}

Sprite* SpriteSheet::getSprite(string name,GameObject* parent){
    auto s = RenderSystem::getSprite(parent);
    sprites[name]->set(s);
    return s;
}

