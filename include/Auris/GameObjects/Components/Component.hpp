#pragma once

class GameObject;

namespace Auris{
class Component {
    public:
        Component(GameObject *gameObject):gameObject(gameObject){};
        virtual ~Component(){
            gameObject = nullptr;
        };

        GameObject* gameObject;
        friend class GameObject;

};

}
