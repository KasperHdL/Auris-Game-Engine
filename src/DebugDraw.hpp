#pragma once

#include "Box2D/Box2D.h"
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Shader.hpp"
#include "SRE/Mesh.hpp"
#include "SRE/Debug.hpp"
#include "glm/glm.hpp"
#include <iostream>

class DebugDraw : public b2Draw
{
    private:

        float m2p = 10.0f;

    public:
        DebugDraw(){}

        void DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color) {
            
            SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));

            for(int i = 0; i < vertexCount-1; i++){
//                std::cout << std::printf("v %i (%f,%f)", i, vertices[i].x, vertices[i].y) << std::endl;
                SRE::Debug::drawLine(glm::vec3(vertices[i].x * m2p,vertices[i].y * m2p,0), glm::vec3(vertices[i+1].x * m2p,vertices[i+1].y * m2p,0)); 
            }

            SRE::Debug::drawLine(glm::vec3(vertices[vertexCount-1].x * m2p,vertices[vertexCount-1].y * m2p,0), glm::vec3(vertices[0].x * m2p,vertices[0].y * m2p,0)); 
//            std::cout << std::endl;
        }

        void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color) {
            DrawPolygon(vertices, vertexCount, color);
        }

        void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
            int const size = 32;
            b2Vec2 array[size];

            for(int i = 0;i < size;i++){
                array[i] = center + b2Vec2(glm::cos(i * (2 * glm::pi<float>() / (float)size )) * radius, glm::sin(i * (2 * glm::pi<float>() / (float)size)) * radius);
            }

            DrawPolygon(&array[0], size, color);
        
        }

        void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
            DrawCircle(center, radius, color);

        }

        void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {

            SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));
            SRE::Debug::drawLine(glm::vec3(p1.x * m2p,p1.y * m2p,0), glm::vec3(p2.x * m2p,p2.y * m2p,0)); 
        }

        void DrawTransform(const b2Transform& xf) {}

        void DrawPoint(const b2Vec2& p, float size, const b2Color& color){
            DrawCircle(p, size, color);
        }


};
