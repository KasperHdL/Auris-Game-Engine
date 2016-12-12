#include "Auris/Testing/DebugUI.hpp"
#include "Auris/Engine.hpp"

using namespace Auris;

//! Startup function
/*! Initializes the DebugUI, starts ImGui and sets required keys for debug input
 * \param engine pointer to the engine
 */
void DebugUI::startup(Engine* engine){
    this->e = engine;
    ImGui_SRE_Init(e->window);
 
    keys.setKey("debug", SDL_SCANCODE_F2);
    keys.setKey("pause", SDL_SCANCODE_F3);
    keys.setKey("stepOne", SDL_SCANCODE_F4);
    keys.setKey("playOnHold", SDL_SCANCODE_F5);
    keys.setKey("drawDebug", SDL_SCANCODE_F6);

    keys.setKey("arrow_up", SDL_SCANCODE_UP);
    keys.setKey("arrow_down", SDL_SCANCODE_DOWN);
    keys.setKey("arrow_left", SDL_SCANCODE_LEFT);
    keys.setKey("arrow_right", SDL_SCANCODE_RIGHT);

 
    e->world->SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit);


}

//! Shutdown the DebugUI
/*! TODO(@Kasper) does nothing currently
 */
void DebugUI::shutdown(){

}

//! update DebugUI
/*! updates ImGui, saves deltatime and memory, 
 * \param deltatime in seconds
 */
void DebugUI::update(float dt){
    runOneStep = false;

    if(Input::keyDown(keys.getKey("stepOne")) || Input::keyHeld(keys.getKey("playOnHold"))){
        runOneStep = true;
        pause = true;
    }

    if(Input::keyDown(keys.getKey("drawDebug"))){
        drawDebug = !drawDebug;
    }


    if (Input::keyDown(keys.getKey("quit"))) {
        this->e->quit = 1;
    }

    if(Input::keyDown(keys.getKey("debug"))){
        debug = !debug;

        if(debug == false){
            ImGui_SRE_NewFrame(e->window);
            ImGui::Render();
        }
    }

    if(Input::keyDown(keys.getKey("pause"))){
        pause = !pause;
    }

    if(debug){
        
        ImGui_SRE_NewFrame(e->window);

        ImGui::Checkbox("Debug(F2)", &debug);
        ImGui::SameLine();
        ImGui::Checkbox("Pause(F3)", &pause);
        if(ImGui::Button("Step One Frame(F4)")){
            runOneStep = true;
            pause = true;
        }
        ImGui::SameLine();
        ImGui::Text("Play on Hold(F5)");
//          ImGui::Checkbox("Toggle Camera Controls(Arrow Keys)",&toggle_cameraControls);
        ImGui::Checkbox("Debug draw(F6)", &drawDebug);

        ImGui::Separator();

        arr_deltaTime[arrIndex] = dt;
        arr_physMem[arrIndex] = e->memLeakDet.getPhysMemUsedByMe();
        arr_virtMem[arrIndex] = e->memLeakDet.getVirtMemUsedByMe();

        if(dt > max_deltaTime)
            max_deltaTime = dt;

        if(e->renderSystem.spritePool.count > max_renderSprites)
            max_renderSprites = e->renderSystem.spritePool.count;

        ImGui::PlotLines("Physical Memory", arr_physMem, arrSize);
        ImGui::Text("Physical Memory: %f / %f", arr_physMem[arrIndex], e->memLeakDet.getTotalPhysMem());
        ImGui::PlotLines("Dt", arr_virtMem, arrSize);
        ImGui::Text("Virtual Memory: %f / %f", arr_virtMem[arrIndex], e->memLeakDet.getTotalVirtMem());

        ImGui::Separator();
        ImGui::PlotLines("Dt", arr_deltaTime, arrSize);
        ImGui::Text("Current Dt: %f - Max dt: %f",dt, max_deltaTime);

        ImGui::Separator();
        ImGui::Text("Num GameObjects %zu", Engine::currentScene->gameObjects.size());
        ImGui::Text("Num of Sprites Allocated %d - Max %d", e->renderSystem.spritePool.count, max_renderSprites);

        ImGui::Separator();

        if(toggle_goInspector){
            ImGui::Begin("GameObject Inspector");
            ImGui::Text("Current scene: %s", Engine::currentScene->name.c_str());
            if(ImGui::TreeNode("GameObjects")){
                int i = 0;
                for(auto& el: Engine::currentScene->gameObjects){
                    string name = el->name;
                    if(name == "") name = &"GO " [ i];

                    ImGui::PushID(&el);
                    if(ImGui::TreeNode(el->name.c_str())){
                        vec2 pos = Convert::toGlm(el->body->GetPosition());
                        ImGui::Text("Position (%f, %f)", pos.x, pos.y);

                        ImGui::Text("Rotation (%f)", el->body->GetAngle());

                        vec2 vel = Convert::toGlm(el->body->GetLinearVelocity());
                        ImGui::Text("Velocity (%f, %f)", vel.x, vel.y);
                        
                        ImGui::Text("Angular Velocity (%f)", el->body->GetAngularVelocity());

                        ImGui::TreePop();
                    }
                    ImGui::PopID();
                    i++;
                }
                ImGui::TreePop();
            }
            ImGui::End();
        }

        arrIndex++;
        if(arrIndex >= arrSize)
            arrIndex = 0;
    }

}

//! Render the Debug UI
/*! calls ImGui::Render() and box2d draw debug if enabled.
 */
void DebugUI::draw(){

    if(debug)
        ImGui::Render();

    if(drawDebug)
        e->world->DrawDebugData();


}
