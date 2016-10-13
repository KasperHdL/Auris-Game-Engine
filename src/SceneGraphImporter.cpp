#include "SceneGraphImporter.hpp"


using namespace SRE;
std::vector<std::shared_ptr<GameObject>> SceneGraphImporter::import(){

    // setup test objec
    Mesh* plane = Mesh::createQuad();
    Mesh* cube  = Mesh::createCube();
    Mesh* sphere = Mesh::createSphere();

    Shader* shader = Shader::getStandard();

    std::vector<std::shared_ptr<GameObject>> gameObjects;
    
    std::vector<GameObjectDescriptor> scene = SceneParser::parseFile("data/car_house_tree.json");
    gameObjects.reserve(scene.size());

    for(auto& g : scene){
        std::string meshName = g.meshName;
        Mesh* mesh;

        if(meshName == "plane")
            mesh = plane;
        else if(meshName == "cube")
            mesh = cube;
        else if(meshName == "sphere")
            mesh = sphere;

        auto go = std::make_shared<GameObject>(mesh, shader);
        go->rotation = glm::vec3(
                glm::radians(g.rotationEuler.x),
                glm::radians(g.rotationEuler.y),
                glm::radians(g.rotationEuler.z)
                );
        go->position = g.position;
        go->scale = g.scale;
        go->color = g.color;

        if(g.parentId != -1){
            go->parent = gameObjects[g.parentId].get();
        }


        gameObjects.push_back(go);
    }


    return gameObjects;
}
