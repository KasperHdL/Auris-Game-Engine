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
#include "Crosshair.hpp"
#include "Auris/Utilities/AudioPlayer.hpp"
#include "Auris/Utilities/Timer.hpp"
#include "Bullet.hpp"
#include "Grenade.hpp"

using namespace std;
using namespace Auris;

class Player : public PhysicsEntity{
public:
    shared_ptr<Animation> anim;
    SpriteSheet* spriteSheet;

    Sprite* lower;
    Sprite* upper;

    Crosshair* crosshair;
    AudioPlayer* audioPlayer;

    Timer pistolReload;
    Timer grenadeReload;

    bool alive = true;
    bool canJump = true;
    bool aiming = false;
    bool canFire = true;
    bool canThrow = true;

    vec2 aimDirection;

    float maxSpeed = 50;
    float jumpHeight = 8000;
    float movementSpeed = 1000;
    float crosshairOffset = 10;
    float bulletOffset = 5;
    float grenadeOffset = 5;
    float aimRotation;
    float deltaTime;

    int healthPoints = 100;
    int pistolShot;
    int controller;

    Player(vec2 position = vec2(0,0)) : PhysicsEntity(){
        type = "Player";

        spriteSheet = AssetManager::getSpriteSheet("player.json", true);

        upper = RenderSystem::getSprite(this);
        spriteSheet->setSpriteTo(upper, "upper_3", true);

        lower = RenderSystem::getSprite(this);
        spriteSheet->setSpriteTo(lower, "lower_run_3");

        anim = RenderSystem::getAnim(this, 1.0f);
        anim->makeSequence(spriteSheet, "lower_run", true);

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

    void init() {
        audioPlayer = (AudioPlayer*) Game::instance->addEntity(make_shared<AudioPlayer>(Game::instance->camera, 1));
        audioPlayer->name = audioPlayer->type + to_string(controller);

        crosshair = (Crosshair*) Game::instance->addEntity(make_shared<Crosshair>());
        crosshair->name = crosshair->type + to_string(controller);

        pistolShot = audioPlayer->addSound(AssetManager::getSound("pistolShot.wav"));

        pistolReload.start(0.2f);
        grenadeReload.start(5.0f);

        aimDirection = vec2(1, 0);

        addChild(audioPlayer);
        addChild(crosshair);
    }

    void setController(int controllerID){
        controller = controllerID;
    }

    void die() {
        alive = false;
        setFixedRotation(false);
        setGravity(0);
        Game::instance->destroyEntity(crosshair);
    }

    void fireBullet(float rotation, vec2 direction) {
        auto bullet = (Bullet*) Game::instance->addEntity(make_shared<Bullet>(vec2(transform->getPosition().x+direction.x*bulletOffset, transform->getPosition().y-direction.y*bulletOffset), rotation, vec2(direction.x, -direction.y), this));
        bullet->player = this;
    }

    void throwGrenade(vec2 direction) {
        auto grenade = (Grenade*) Game::instance->addEntity(make_shared<Grenade>(vec2(transform->getPosition().x+direction.x*grenadeOffset, transform->getPosition().y-direction.y*grenadeOffset), vec2(direction.x, -direction.y)));
    }

    void update(float deltaTime){
        this->deltaTime = deltaTime;
        if (alive){
            float leftStickX = Input::getControllerAxisState(controller, SDL_CONTROLLER_AXIS_LEFTX);
            leftStickX = leftStickX/32767;

            float leftStickY = Input::getControllerAxisState(controller, SDL_CONTROLLER_AXIS_LEFTY);
            leftStickY = leftStickY/32767;

            vec2 rightStick = Input::getControllerRightStickState(controller);
            rightStick = vec2(rightStick.x / 32767, rightStick.y / 32767);

            int rightTrigger = Input::getControllerAxisState(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

            if ((Input::getControllerButtonState(controller, SDL_CONTROLLER_BUTTON_A)) && canJump) {
                applyForce(vec2(0, 1) * jumpHeight, true);
                canJump = false;
            }

            if (leftStickX < 0)  {
                anim->run(lower, abs(leftStickX)*deltaTime, true);
                //transform->scale = vec2(-1, 1);
                if (getLinearVelocity()[0] > -maxSpeed)
                    applyForce(vec2(1, 0) * leftStickX * movementSpeed, true);
            }

            if (leftStickX > 0)  {
                anim->run(lower, abs(leftStickX)*deltaTime, false);
                //transform->scale = vec2(1, 1);
                if (getLinearVelocity()[0] < maxSpeed)
                    applyForce(vec2(1, 0) * leftStickX * movementSpeed, true);
            }

            if (rightStick != vec2(0, 0)) {
                aimDirection = rightStick;

                aiming = true;
            }
            else {
                aiming = false;
            }

            aimRotation = (float)(atan2(aimDirection.x, -aimDirection.y));
            vec2 normalized = normalize(aimDirection);

            if (aiming) {
                float divider = 180/7;
                float absDir = abs(degrees(aimRotation));
                int aim = absDir > 180-divider ? 6 :
                    absDir > 180-divider*2 ? 5 :
                    absDir > 180-divider*3 ? 4 :
                    absDir > 180-divider*4 ? 3 :
                    absDir > 180-divider*5 ? 2 :
                    absDir > 180-divider*6 ? 1 : 0;

                string sprite   = "upper_" + to_string(aim);
                spriteSheet->setSpriteTo(upper, sprite, normalized.x < 0);
            }

            if (rightTrigger > 16000) {
                if (canFire) {
                    audioPlayer->playSound(pistolShot);
                    fireBullet(-aimRotation-(radians(90.0f)), normalized);
                    canFire = false;
                    pistolReload.reset();
                }
            }

            if (Input::getControllerButtonState(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
                throwGrenade(normalized);
                canThrow = false;
                grenadeReload.reset();
            }

            if (healthPoints <= 0) {
                healthPoints = 0;
                die();
            }

            crosshair->transform->setPosition(vec2(normalized.x*crosshairOffset, -normalized.y*crosshairOffset));
        }

        if (pistolReload.time(deltaTime))
            canFire = true;

        if (grenadeReload.time(deltaTime))
            canThrow = true;
    }

    void OnCollisionEnter(PhysicsEntity* other) {
        if (other->type == "jumpable")
            canJump = true;

        if (other->type == "Bullet") {
            Bullet* bullet = (Bullet*) other;
            if (bullet->player != this) {
                healthPoints -= bullet->damage;
                other->setGravity(3);
                other->setFixedRotation(false);
                other->setBullet(false);
                Game::instance->destroyEntity(other);
            }
        }

        if (other->type == "Explosion") {
            Grenade* grenade = (Grenade*) other;
            healthPoints -= grenade->damage;
        }
    }

    void OnCollisionExit(PhysicsEntity* other) {
        if (other->type == "jumpable")
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
