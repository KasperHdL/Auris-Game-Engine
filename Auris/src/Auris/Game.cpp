#include "Auris/Game.hpp"

using namespace std;
namespace Auris {
Entity* Game::addEntity(std::shared_ptr<Entity> entity) {
    Game::entities.push_back(entity);
    return entity.get();
}
}
