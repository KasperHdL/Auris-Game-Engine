#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <SRE/SimpleRenderEngine.hpp>
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>


using namespace glm;

class GameObject{
public:

    GameObject(SRE::Mesh* mesh, SRE::Shader* shader);

    void draw();

    vec4 color;

    GameObject* parent;
    vec3 position;
    vec3 scale;
    vec3 rotation;

    mat4 localTransform();
    mat4 globalTransform();

private:
    SRE::Mesh* mesh;
    SRE::Shader* shader;


};
