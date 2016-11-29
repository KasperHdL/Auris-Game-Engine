#pragma once

#include "Auris/GameObjects/GameObject.hpp"
#include "Auris/GameObjects/Components/Sprite.hpp"
#include "Auris/GameObjects/Components/Animation.hpp"

#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/GameObjects/Components/Material.hpp"

#include "Auris/GameObjects/Components/SpriteSheet.hpp"
#include "Auris/Utility/Resource.hpp"
#include "Auris/Utility/BodyStandard.hpp"

#include "SRE/Texture.hpp"


using namespace std;
class Player : public GameObject{
    public:
    shared_ptr<Animation> anim;

    Player(vec2 position = vec2(0,0)):GameObject(){
        name = "Player";

        SpriteSheet* ss = new SpriteSheet(SRE::Texture::createFromFile(Resource::getPath("MarioPacked.png").c_str(),false),Resource::getPath("MarioPacked.json"));

        sprite = ss->getSprite("mario_10",this);

        anim = RenderSystem::getAnim(this, 4.0f);
        anim->setSheet(ss);

        b2CircleShape shape;
        shape.m_radius = (19 * Constants::PIXELS_TO_METERS);
        body = Utility::BodyStandard::getDynamicBody(&shape, position);

        enableCollisionEvents();
    }

    ~Player(){
        //RenderSystem::deleteAnim(anim);
    }

	float force;
	Keys keys;
	void Init() {
		force = 10000.0f;
	}

    void Update(float dt){
        anim->setSprite(sprite);
		if (Input::keyHeld(keys.getKey("up"))) {
			body->ApplyForceToCenter(b2Vec2(0, force), true);
		}
		if (Input::keyHeld(keys.getKey("down"))) {
			body->ApplyForceToCenter(b2Vec2(0, -force), true);
		}
		if (Input::keyHeld(keys.getKey("left"))) {
			body->ApplyForceToCenter(b2Vec2(-force, 0), true);
		}
		if (Input::keyHeld(keys.getKey("right"))) {
			body->ApplyForceToCenter(b2Vec2(force, 0), true);
		}
    }

    void OnCollisionEnter(GameObject* other) {
        cout << name << " hit " << other->name << endl;
    }

    void OnCollisionExit(GameObject* other) {
        cout << name << " is longer colliding with " << other->name << endl;
    }
};
