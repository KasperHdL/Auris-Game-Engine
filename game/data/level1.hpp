#pragma once

#include "../../engine/src/Auris.hpp"
#include "../../engine/src/GameObjects/Player.hpp"
#include "../../engine/src/GameObjects/Wall.hpp"

class Level1 : public Scene {
public:
    void init() {
        name = "Level 1";

        addGameObject(make_shared<Player>(Auris::world, vec2(10, 10)));
        addGameObject(make_shared<Player>(Auris::world, vec2(20, 10)));
        addGameObject(make_shared<Player>(Auris::world, vec2(30, 10)));
        addGameObject(make_shared<Player>(Auris::world, vec2(40, 10)));
    }
};
