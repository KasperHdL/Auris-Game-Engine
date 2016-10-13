#pragma once

#include <vector>
#include <string>
#include <memory>

#include "GameObject.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Shader.hpp"
#include "SceneParser.hpp"

class SceneGraphImporter{
    public:
        SceneGraphImporter(){};
        ~SceneGraphImporter(){};
        
        std::vector<std::shared_ptr<GameObject>> import();
};
