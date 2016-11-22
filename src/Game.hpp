#include "Auris.hpp"


class Game {
    vector<shared_ptr<GameObject>> gameObjects;

    void init() {
        Auris engine(width, height);
        engine.startup();
    }

    void update() {

    }

    void shutdown();

    gameObjects.push_back(make_shared<Player>(world,vec2(10,10)));
    gameObjects.push_back(make_shared<Player>(world));
    gameObjects.push_back(make_shared<Wall>(world, vec2(30, 30)));
};
