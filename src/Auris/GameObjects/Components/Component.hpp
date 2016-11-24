#pragma once

class GameObject;
class Component {
    public:
        Component(GameObject *gameObject):gameObject(gameObject){};
        virtual ~Component(){};

        GameObject* gameObject;
        friend class GameObject;

};

