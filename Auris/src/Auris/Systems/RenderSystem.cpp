#include "Auris/Systems/RenderSystem.hpp"

using namespace Auris;
DynamicPool<Sprite> RenderSystem::spritePool = DynamicPool<Sprite>(16);
vector<shared_ptr<Animation>> RenderSystem::animations;

void RenderSystem::startup(int reserve){
}

void RenderSystem::shutdown(){
    RenderSystem::animations.clear();
}


void RenderSystem::update(float dt){
    for(int i = 0; i < RenderSystem::spritePool.capacity;i++){
        Sprite* s = RenderSystem::spritePool[i];
        if(s != nullptr)
            s->draw(); //draw all sprites
    }

}

Sprite* RenderSystem::getSprite(Entity* entity, SRE::Texture* texture, Auris::Mesh* mesh, SRE::Texture* normalMap){
    if(texture != nullptr && mesh == nullptr){

        float w = texture->getWidth();
        float h = texture->getHeight();

        float nhw = -w/2;
        float nhh = -h/2;

        std::vector<glm::vec3> vertices({
            glm::vec3{ w + nhw, nhh, 0 }, 
            glm::vec3{ w + nhw, h + nhh, 0 },
            glm::vec3{ nhw, nhh, 0 },

            glm::vec3{ nhw, nhh, 0 }, 
            glm::vec3{ w + nhw, h + nhh, 0 }, 
            glm::vec3{ nhw, h + nhh, 0 }
        });

        // Per pixel normals are used for 2D graphics, but the mesh still needs an empty normal vector
        std::vector<glm::vec3> normals;

        // UVs contains the normalized texture coordinates.

        std::vector<glm::vec2> uvs({
            glm::vec2{ 1, 0 }, glm::vec2{ 1, 1 }, glm::vec2{ 0, 0 },
            glm::vec2{ 0, 0 }, glm::vec2{ 1, 1 }, glm::vec2{ 0, 1 }
        });

        mesh = new Mesh(vertices, normals, uvs ,w, h);

    }

    Sprite* s = new (RenderSystem::spritePool.create()) Sprite(entity, texture, normalMap, mesh);
    return s;
}

shared_ptr<Animation> RenderSystem::getAnim(Entity* entity, float length){
    shared_ptr<Animation> a = make_shared<Animation>(entity, length);
    RenderSystem::animations.push_back(a);
    return a;
}

void RenderSystem::deleteSprite(Sprite* sprite){
    RenderSystem::spritePool.remove(sprite);
}

void RenderSystem::deleteAnim(shared_ptr<Animation> ani){
    if(RenderSystem::animations.size() == 0){
        std::cout << "No Animations to delete" << std::endl;
        return;
    }

    int index = 0;
    for (auto& el : RenderSystem::animations){
        if(ani == el)
            break;
        index++;
    }
    RenderSystem::animations.erase(RenderSystem::animations.begin() + index);
}
