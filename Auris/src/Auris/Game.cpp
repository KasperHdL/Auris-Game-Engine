#include "Auris/Game.hpp"

namespace Auris {

Game* Game::instance = nullptr;
Game::Game(){
    if(instance != nullptr){
        std::cerr << "Multiple versions of Game initialized. Only a single instance is supported." << std::endl; 
    }
    instance = this;
}
    
}
