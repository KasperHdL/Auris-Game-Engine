#pragma once

class GameObject;
class Component {
    public:
        Component(GameObject *gameObject):gameObject(gameObject){}

        GameObject* gameObject;
        friend class GameObject;

};

