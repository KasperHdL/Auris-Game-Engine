#include "GameObject.hpp"

#include "Components/CTransform.hpp"

GameObject::GameObject(){
    components = vector<shared_ptr<Component>>();
    components.reserve(8);
    transform = addComponent<CTransform>();
}


bool GameObject::removeComponent(std::shared_ptr<Component> ptr){
    for(auto iter = components.begin(); iter != components.end(); iter++){
        if(*iter == ptr){
            components.erase(iter);
            ptr.reset();
            return true;
        }
    }
    return false;
}
