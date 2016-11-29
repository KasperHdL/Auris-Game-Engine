#pragma once

class GameObject;
class Component {
    public:
        Component(GameObject *gameObject):gameObject(gameObject){};
        virtual ~Component(){
            gameObject = nullptr;
        };

        GameObject* gameObject;
        friend class GameObject;

};

