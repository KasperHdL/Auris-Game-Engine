#pragma once

class GameObject;
class Component {
    protected:
        Component(GameObject *gameObject):gameObject(gameObject){};

        friend class GameObject;

    public:
        virtual ~Component(){};
        GameObject* gameObject;


};

