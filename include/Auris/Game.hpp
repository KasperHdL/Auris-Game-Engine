#pragma once

#include "Auris/Engine.hpp"
#include "Auris/Systems/Scene.hpp"
#include "Auris/Entity.hpp"
#include "Auris/Entities/Camera.hpp"
#include <vector>
#include <memory>

namespace Auris{
class Game {

public:
    Auris::Camera* camera;

    virtual void init() = 0;

    virtual void earlyUpdate(float dt) = 0;

    virtual void update(float dt) = 0;

    virtual void lateUpdate(float dt) = 0;

    virtual void debugDraw(){}

    virtual void shutdown() = 0;

    virtual void controllerConnected(){}

    virtual void controllerActivated(int controllerID){}

    virtual void controllerDisconnected(int controllerID){}
    std::vector<std::shared_ptr<Entity>> entities;

    inline int addEntity(std::shared_ptr<Entity> entity){
        entities.push_back(entity);
        return entities.size()-1;
    }

    void loadScene(Scene* scene) {
        // Load new scene and init entities
        scene->init(this);

        for (auto & el : entities)
            el->init();
    }


};
}
