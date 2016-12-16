#include "Auris/Testing/DebugUI.hpp"
#include "Auris/Engine.hpp"

using namespace Auris;
void DebugUI::startup(Engine* engine){
    this->e = engine;
  
    Engine::world->SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit);

}

void DebugUI::shutdown(){

}

void DebugUI::update(float dt){
    runOneStep = false;

    if(Input::keyDown(Auris::Action::stepOne) || Input::keyHeld(Auris::Action::playOnHold)){
        runOneStep = true;
        pause = true;
    }

    if(Input::keyDown(Auris::Action::drawDebug))
        drawDebug = !drawDebug;
    

    if(Input::keyDown(Auris::Action::drawColliders))
        drawColliders = !drawColliders;

    if(Input::keyDown(Auris::Action::debug_menu))
        debug_menu = !debug_menu;
    
    if(Input::keyDown(Auris::Action::pause))
        pause = !pause;
   
    if(Input::keyDown(Auris::Action::toggleProfiler))
        profiling = !profiling;

    if(Input::keyDown(Auris::Action::toggleHierarchy))
        toggle_hierarchy = !toggle_hierarchy;

    if(Input::keyDown(Auris::Action::toggleInspector))
        toggle_inspector = !toggle_inspector;


    if(debug_menu){
        
        ImGui::Begin("Debug Menu");
        {
            ImGui::Checkbox("Debug(F2)[this]", &debug_menu);
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
            ImGui::Checkbox("Toggle Hierarchy", &toggle_hierarchy);
            ImGui::Checkbox("Toggle Inspector", &toggle_inspector);
            ImGui::Checkbox("Toggle Profiling inspector", &profiling);
        }
        ImGui::End();
    }

    if(profiling){
        ImGui::Begin("Profiling:");
        {

            if(dt > max_deltaTime)
                max_deltaTime = dt;

            if(e->renderSystem.spritePool.count > max_renderSprites)
                max_renderSprites = e->renderSystem.spritePool.count;

            ImGui::PlotLines("Physical Memory", arr_physMem, arrSize);
            ImGui::Text("Physical Memory: %f / %f", arr_physMem[arrIndex], memLeakDet.getTotalPhysMem());
            ImGui::PlotLines("Dt", arr_virtMem, arrSize);
            ImGui::Text("Virtual Memory: %f / %f", arr_virtMem[arrIndex], memLeakDet.getTotalVirtMem());
 

            arr_deltaTime           [ arrIndex] = dt;
            arr_physMem             [ arrIndex] = memLeakDet.getPhysMemUsedByMe();
            arr_virtMem             [ arrIndex] = memLeakDet.getVirtMemUsedByMe();
            arr_profInput           [ arrIndex] = e->profile_InputTimer.length;
            arr_profEntityUpdate    [ arrIndex] = e->profile_Entity_UpdateTimer.length;
            arr_profGEarlyUpdate    [ arrIndex] = e->profile_Game_EarlyUpdateTimer.length;
            arr_profGUpdate         [ arrIndex] = e->profile_Game_UpdateTimer.length;
            arr_profGLateUpdate     [ arrIndex] = e->profile_Game_LateUpdateTimer.length;
            arr_profPhysics         [ arrIndex] = e->profile_PhysicsTimer.length;
            arr_profUpdateTransform [ arrIndex] = e->profile_UpdatePhysicsEntityTransformTimer.length;
            arr_profRender          [ arrIndex] = e->profile_RenderTimer.length;

            ImGui::Text("Num Entities %zu", Game::entities.size());
            ImGui::Text("Num of Sprites Allocated %d - Max %d", e->renderSystem.spritePool.count, max_renderSprites);

            ImGui::Separator();
            ImGui::PlotLines("Dt", arr_deltaTime, arrSize);
            ImGui::Text("Current Dt: %f - Max dt: %f",dt, max_deltaTime);

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



        }
        ImGui::End();
    }


    int countOpen = 0;
    if(toggle_hierarchy){
        ImGui::Begin("Hierarchy");
        {

            int i = 0;
            int numWithNoName = 0;
            for(auto& ent: Game::entities){
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
                                for(auto& q: Game::entities){
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

                if(toggle_inspector){
                    if(entityInspectorOpen[i]){
                        ImGui::Begin("Inspector");
                        {
                            if(countOpen > 0){
                                ImGui::Separator();
                                ImGui::Separator();
                            }

                            if(ImGui::TreeNode(name.c_str())){
                                /* Child Toggle Parent in Inspector
                                if(ent->parent != nullptr){

                                    int k = 0;
                                    for(auto& q: e->game->entities){
                                        if(ent->parent == q.get()) break;
                                        k++;
                                    }

                                    ImGui::Checkbox(("Parent: " + ent->parent->name).c_str(),&entityInspectorOpen[k]);
                                }
                                */

                                ent->inspectorImGui();
                                ImGui::TreePop();
                            }
                            countOpen++;
                        }
                        ImGui::End();
                    }
                }
                i++;


            }
            ImGui::Text("Num Entities with no name: %d", numWithNoName);
        }
        ImGui::End();
    }


    if(toggle_inspector && countOpen == 0){
        ImGui::Begin("Inspector");
        ImGui::Text("Select Entities in the Hierarchy");
        ImGui::End();
    }


    arrIndex++;
    if(arrIndex >= arrSize)
        arrIndex = 0;

    e->game->drawDebugImGui();


}

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
