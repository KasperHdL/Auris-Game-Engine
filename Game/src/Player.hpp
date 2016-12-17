#pragma once

#include "SRE/Texture.hpp"
#include "Auris/Entities/Nuggets/Sprite.hpp"
#include "Auris/Entities/Nuggets/Animation.hpp"
#include "Auris/Systems/RenderSystem.hpp"
#include "Auris/Constants.hpp"
#include "Auris/Systems/Input.hpp"
#include "Auris/Entities/Nuggets/Material.hpp"
#include "Auris/Utilities/SpriteSheet.hpp"
#include "Auris/Utilities/BodyStandard.hpp"
#include "Auris/Utilities/AssetManager.hpp"
#include "Auris/Entities/PhysicsEntity.hpp"
#include "Auris/Action.hpp"

#include "Bullet.hpp"

using namespace std;
using namespace Auris;

class Player : public PhysicsEntity{
public:
    shared_ptr<Animation> anim;
    SpriteSheet* spriteSheet;

    Sprite* lower;
    Sprite* upper;

    bool alive = true;
    bool canJump = true;
    bool aiming = false;

    float maxSpeed = 50;
    float jumpHeight = 8000;
    float movementSpeed = 1000;
    float crosshairOffset = 10;
    float aimDirection;

    int healthPoints = 100;

    int controller;

    Player(vec2 position = vec2(0,0)) : PhysicsEntity(){
        type = "Player";

        spriteSheet = AssetManager::getSpriteSheet("player.json", true);
        upper = RenderSystem::getSprite(this);
        spriteSheet->setSpriteTo(upper, "upper_3", true);

        anim = RenderSystem::getAnim(this, 1.0f);
        anim->makeSequence(spriteSheet, "lower_run");

        lower = RenderSystem::getSprite(this);
        spriteSheet->setSpriteTo(lower, "lower_run_3");

        upper->offset = vec3(3,8,0);
        lower->offset = vec3(3,4,0);

        b2PolygonShape shape;
        shape.SetAsBox(((lower->getWidth()/3) * Constants::PIXELS_TO_METERS),(upper->getHeight() + lower->getHeight()-9)/3 * Constants::PIXELS_TO_METERS);

        body = Auris::Utilities::BodyStandard::getDynamicBody(&shape,position);

        // Physics properties
        setCollisionEvents(true);
        setFixedRotation(true);
        setGravity(3.0f);
    }

    ~Player(){
        RenderSystem::deleteAnim(anim);
        RenderSystem::deleteSprite(lower);
        RenderSystem::deleteSprite(upper);
    }

    void setController(int controllerID){
        this->controller = controllerID;
    }

    void die() {
        alive = false;
        setFixedRotation(false);
        setGravity(0);
    }

    void fireBullet(float rotation, vec2 direction) {
        auto bullet = (Bullet*) Game::instance->addEntity(make_shared<Bullet>(transform->getPosition()));
        bullet->setRotation(rotation);
        bullet->direction = direction;
    }

    void init() {

	}

    void update(float dt){
        if (alive){
            float leftStickX = Input::getControllerAxisState(controller, SDL_CONTROLLER_AXIS_LEFTX);
            leftStickX = leftStickX/32767;

            float leftStickY = Input::getControllerAxisState(controller, SDL_CONTROLLER_AXIS_LEFTY);
            leftStickY = leftStickY/32767;

            vec2 rightStick = Input::getControllerRightStickState(controller);
            rightStick = vec2(rightStick.x / 32767, rightStick.y / 32767);

            int rightTrigger = Input::getControllerAxisState(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

            if ((Input::getControllerButtonState(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) | Input::getControllerButtonState(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) & canJump) {
                applyForce(vec2(0, 1) * jumpHeight, true);
                canJump = false;
            }

            if (leftStickX < 0)  {
                anim->run(lower, abs(leftStickX)*dt);
                //transform->setScale = vec2(-1, 1);
                if (getLinearVelocity()[0] > -maxSpeed)
                    applyForce(vec2(1, 0) * leftStickX * movementSpeed, true);
            }

            if (leftStickX > 0)  {
                anim->run(lower, abs(leftStickX)*dt);
                //transform->setScale = vec2(1, 1);
                if (getLinearVelocity()[0] < maxSpeed)
                    applyForce(vec2(1, 0) * leftStickX * movementSpeed, true);
            }

            if (rightStick != vec2(0, 0)) {
                aimDirection = (float)(atan2(rightStick.x, -rightStick.y));
                aimDirection = degrees(aimDirection);
                getChildByType("crosshair")->transform->getPosition() = vec3(rightStick*crosshairOffset, 0);
                aiming = true;
            }
            else
                aiming = false;

            if (aiming) {
                float divider = 180/7;
                int aim = abs(aimDirection) > 180-divider ? 0 :
                    abs(aimDirection) > 180-divider*2 ? 1 :
                    abs(aimDirection) > 180-divider*3 ? 2 :
                    abs(aimDirection) > 180-divider*4 ? 3 :
                    abs(aimDirection) > 180-divider*5 ? 4 :
                    abs(aimDirection) > 180-divider*6 ? 5 : 6;
                string sprite   = "upper_" + to_string(aim);
                spriteSheet->setSpriteTo(upper, sprite, rightStick.x < 0);
                if (rightTrigger > 16000) {
                    fireBullet(aimDirection, rightStick);
                }
            }
        }
    }

    void OnCollisionEnter(PhysicsEntity* other) {
        if (other->type == "Wall")
            canJump = true;

        if (other->type == "Bullet") {
            healthPoints -= ((Bullet*)other)->damage;
            other->setGravity(3);
            other->setFixedRotation(false);
            other->setBullet(false);
        }
    }

    void OnCollisionExit(PhysicsEntity* other) {
        canJump = false;
    }

    void inspectorImGui(){
        PhysicsEntity::inspectorImGui();
        ImGui::Separator();

        ImGui::Checkbox("Is Alive", &alive);
        ImGui::Checkbox("Can Jump", &canJump);

        ImGui::DragInt("Health Points", &healthPoints);

        ImGui::DragFloat("MaxSpeed", &maxSpeed);
        ImGui::DragFloat("jumpHeight", &jumpHeight);
        ImGui::DragFloat("movementSpeed", &movementSpeed);

    }
};
