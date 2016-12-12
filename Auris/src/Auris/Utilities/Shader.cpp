#include "Auris/Utilities/Shader.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Texture.hpp"
#include "SRE/BlendType.hpp"


namespace Auris{
    SRE::Shader* Shader::litSprite = nullptr;
    SRE::Shader* Shader::getLitSprite() {
        if (litSprite != nullptr){
            return litSprite;
        }
        const char* vertexShader = R"(#version 140
        in vec4 position;
        in vec3 normal;
        in vec2 uv;
        out vec2 vUV;
        out vec3 objPos;
        
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        
        void main(void) {
            vec4 obj = model * position;
            gl_Position = projection * view * objPos;
            
            vUV = uv;
            objPos = obj.xyz;
        }
        )";
        const char* fragmentShader = R"(#version 140
        out vec4 fragColor;
        in vec2 vUV;
        int vec3 objPos;
        
        uniform vec4 ambientLight;
        uniform vec4 color;
        uniform sampler2D tex;
        uniform sampler2D normalMap;

        uniform vec4 lightPosType[4];
        uniform vec4 lightColorRange[4];
        
        void main(void)
        {
            vec4 lightColor = ambientLight.xyz;
            vec4 normal = texture(normalMap, vUV);

            for( int i=0;i<4;i++){
                bool isDirectional = lightPosType[0].w == 0.0;
                bool isPoint = lightPosType[0].w == 1.0;

                vec3 lightDirection;
                float att = 1.0;
                if(isDirectional){
                    lightDirection = lightPosType[i].xyz;
                }else if (isPoint){
                    vec3 lightVector = objPos.xyz - lightPosType[i].xyz;
                    float lightRange = lightColorRange[i].w;
                    lightDirection = lightVector / lightVectorLength;

                }



            }
            fragColor = color * texture(tex, vUV);
        }
        )";
        litSprite = createShader(vertexShader, fragmentShader);
        litSprite->set("color", glm::vec4(1));
        litSprite->set("normalMap", SRE::Texture::getWhiteTexture());
        litSprite->set("tex", SRE::Texture::getWhiteTexture());
        litSprite->setBlend(SRE::BlendType::AlphaBlending);
        litSprite->setDepthTest(false);
        return litSprite;
    }
}