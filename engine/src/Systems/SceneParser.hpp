#pragma once

#include "picojson.h"
#include <fstream>
#include "glm/glm.hpp"
#include "Box2D/Box2D.h"
#include "../Auris.hpp"

using namespace std;

class GameObjectDescriptor {
public:
    // Uniquely defines a game object
    int uniqueId;

    string name;

    // transform
    // position relative to parent
    glm::vec2 position;

    // rotation relative to parent
    glm::vec2 rotationEuler;

    // scale relative to parent
    glm::vec2 scale;

    // parent id (-1 means no parent)
    int parentId;
};


class SceneParser{
public:
    glm::vec2 to_vec2(picojson::value v){
        glm::vec3 res;
        auto array = v.get<picojson::array>();
        for (int i=0;i<3;i++){
            res[i] = (float)array[i].get<double>();
        }
        return res;
    }

    vector<GameObjectDescriptor> parseFile(string filename){
        fstream file(filename);
        picojson::value v;
        file >> v;

        std::vector<GameObjectDescriptor> res;
        for (auto o : v.get("gameobjects").get<picojson::array>()){
            GameObjectDescriptor d;
            d.uniqueId = (int)o.get("uniqueId").get<double>();
            d.name = o.get("name").get<string>();
            d.position = to_vec2(o.get("position"));
            d.rotationEuler = o.get("rotationEuler");
            d.scale = to_vec2(o.get("scale"));
            d.parentId = (int)o.get("parentId").get<double>();

            res.push_back(d);
        }
        return res;
    }

    void loadScene(string level){
        vector<GameObjectDescriptor> scene = parseFile(level);
        for (auto & el : scene) {
            Auris::addGameObject(make_shared<GameObject>(Auris::world, el.position));
        }
    }
};
