#include "Auris/Testing/DebugUI.hpp"
#include "Auris/Engine.hpp"

using namespace Auris;

//! Startup function
/*! Initializes the DebugUI, starts ImGui and sets required keys for debug input
 * \param engine pointer to the engine
 */
void DebugUI::startup(Engine* engine){
    this->e = engine;
  
    Engine::world->SetDebugDraw(&debugDraw);
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

    if(Input::keyDown(Auris::Action::stepOne) || Input::keyHeld(Auris::Action::playOnHold)){
        runOneStep = true;
        pause = true;
    }

    if(Input::keyDown(Auris::Action::drawDebug)){
        drawDebug = !drawDebug;
    }

    if(Input::keyDown(Auris::Action::drawColliders)){
        drawColliders = !drawColliders;
    }

    if(Input::keyDown(Auris::Action::debug)){
        debug = !debug;

    }

    if(Input::keyDown(Auris::Action::pause)){
        pause = !pause;
    }

    if(debug){
        
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
        ImGui::Checkbox("Debug Colliders(F6)", &drawColliders);
        ImGui::Checkbox("Call DrawDebug on Entities(F7)", &drawDebug);

        ImGui::Separator();
        ImGui::Checkbox("Toggle Entity inspector", &toggle_goInspector);
        ImGui::Checkbox("Toggle Profiling inspector", &profiling);

        ImGui::Separator();

        arr_deltaTime[arrIndex] = dt;
        arr_physMem[arrIndex] = memLeakDet.getPhysMemUsedByMe();
        arr_virtMem[arrIndex] = memLeakDet.getVirtMemUsedByMe();

        if(dt > max_deltaTime)
            max_deltaTime = dt;

        if(e->renderSystem.spritePool.count > max_renderSprites)
            max_renderSprites = e->renderSystem.spritePool.count;

        ImGui::PlotLines("Physical Memory", arr_physMem, arrSize);
        ImGui::Text("Physical Memory: %f / %f", arr_physMem[arrIndex], memLeakDet.getTotalPhysMem());
        ImGui::PlotLines("Dt", arr_virtMem, arrSize);
        ImGui::Text("Virtual Memory: %f / %f", arr_virtMem[arrIndex], memLeakDet.getTotalVirtMem());

        ImGui::Separator();
        ImGui::PlotLines("Dt", arr_deltaTime, arrSize);
        ImGui::Text("Current Dt: %f - Max dt: %f",dt, max_deltaTime);

        ImGui::Separator();
        ImGui::Text("Num Entities %zu", e->game->entities.size());
        ImGui::Text("Num of Sprites Allocated %d - Max %d", e->renderSystem.spritePool.count, max_renderSprites);

        ImGui::Separator();

        if(profiling){
            ImGui::Begin("Profling:");

            arr_profInput           [arrIndex] = e->profile_InputTimer.length;
            arr_profEntityUpdate    [arrIndex] = e->profile_Entity_UpdateTimer.length;
            arr_profGEarlyUpdate    [arrIndex] = e->profile_Game_EarlyUpdateTimer.length;
            arr_profGUpdate         [arrIndex] = e->profile_Game_UpdateTimer.length;
            arr_profGLateUpdate     [arrIndex] = e->profile_Game_LateUpdateTimer.length;
            arr_profPhysics         [arrIndex] = e->profile_PhysicsTimer.length;
            arr_profUpdateTransform [arrIndex] = e->profile_UpdatePhysicsEntityTransformTimer.length;
            arr_profRender          [arrIndex] = e->profile_RenderTimer.length;


            ImGui::PlotLines("Input", arr_profInput, arrSize);
            ImGui::Text("Input %f", e->profile_InputTimer.length);

            ImGui::PlotLines("Entity Update", arr_profEntityUpdate, arrSize);
            ImGui::Text("Entity update %f", e->profile_Entity_UpdateTimer.length);

            ImGui::PlotLines("Game Early Update", arr_profGEarlyUpdate, arrSize);
            ImGui::Text("Game early update %f", e->profile_Game_EarlyUpdateTimer.length);
            ImGui::PlotLines("Game Update", arr_profGUpdate, arrSize);
            ImGui::Text("Game update %f", e->profile_Game_UpdateTimer.length);
            ImGui::PlotLines("Game Late Update", arr_profGLateUpdate, arrSize);
            ImGui::Text("Game late update %f", e->profile_Game_LateUpdateTimer.length);

            ImGui::PlotLines("Physics", arr_profPhysics, arrSize);
            ImGui::Text("Physics %f", e->profile_PhysicsTimer.length);
            ImGui::PlotLines("PhysicsEntity Update Transform", arr_profUpdateTransform, arrSize);
            ImGui::Text("PhysicsEntity update transform %f", e->profile_UpdatePhysicsEntityTransformTimer.length);

            ImGui::PlotLines("Render", arr_profRender, arrSize);
            ImGui::Text("Render %f", e->profile_RenderTimer.length);

            ImGui::End();
        }


        if(toggle_goInspector){
            ImGui::Begin("Entities Inspector");

            int i = 0;
            int numWithNoName = 0;
            for(auto& ent: e->game->entities){
                if(i >= entityInspectorOpenSize)
                    continue;

                string name = ent->name;
                if(name == ""){
                    numWithNoName++;
                    i++;
                    continue;
                }


                if(ent->parent == nullptr){
                    ImGui::PushID(&entityInspectorOpen);
                    if(ent->children.size() > 0){
                        ImGui::Checkbox("",&entityInspectorOpen[i]);
                        ImGui::SameLine();
                        if(ImGui::TreeNode(name.c_str())){
                            for(int j = 0; j < ent->children.size(); j++){

                                int k = 0;
                                for(auto& q: e->game->entities){
                                    if(ent->children[j] == q.get()) break;
                                    k++;
                                }

                                ImGui::Checkbox(ent->children[j]->name.c_str(),&entityInspectorOpen[k]);


                            }
                            ImGui::TreePop();

                        }
                    }else{
                        ImGui::Checkbox(ent->name.c_str(),&entityInspectorOpen[i]);
                    }
                    ImGui::PopID();
                }

                if(entityInspectorOpen[i]){
                    ImGui::PushID(&entityInspectorOpen);
                    ImGui::Begin(name.c_str());
                    if(ent->parent != nullptr){

                        int k = 0;
                        for(auto& q: e->game->entities){
                            if(ent->parent == q.get()) break;
                            k++;
                        }

                        ImGui::Checkbox(("Parent: " + ent->parent->name).c_str(),&entityInspectorOpen[k]);
                    }

                    ent->inspectorImGui();
                    ImGui::End();
                    ImGui::PopID();
                }
                i++;

            }

            ImGui::Text("Num Entities with no name: %d", numWithNoName);



            ImGui::End();
        }

        arrIndex++;
        if(arrIndex >= arrSize)
            arrIndex = 0;

        e->game->drawDebugImGui();
    }

}

//! Draws debug information in world 
/*! calls debugdraw on entities and draws box2d debug if drawdebug and draw colliders is enabled respectively
*/
void DebugUI::draw(){


    if(drawDebug){
        for(auto& ent: e->game->entities){
            ent->debugDraw();
        }
    }

    if(drawColliders){
        Engine::world->DrawDebugData();
    }


}
