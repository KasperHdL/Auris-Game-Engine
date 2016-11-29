#pragma once

#include "../../engine/src/Auris.hpp"
#include "../../engine/src/GameObjects/Player.hpp"
#include "../../engine/src/GameObjects/Wall.hpp"

class Level2 : public Scene {
public:
    void init() {
        name = "Level 2";

        addGameObject(make_shared<Player>(Auris::world, vec2(10, 10)));
        addGameObject(make_shared<Player>(Auris::world, vec2(10, 20)));
        addGameObject(make_shared<Player>(Auris::world, vec2(10, 30)));
        addGameObject(make_shared<Player>(Auris::world, vec2(10, 40)));
    }
};
