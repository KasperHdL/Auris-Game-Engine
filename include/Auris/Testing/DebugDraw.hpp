#pragma once

#include "Box2D/Box2D.h"
#include "SRE/Debug.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/constants.hpp>
#include <iostream>

#include "Auris/Constants.hpp"

namespace Auris{
class DebugDraw : public b2Draw{
public:
    DebugDraw(){}

    void DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color) {
        //std::cout << color.r << " " << color.g << " " << color.b << " " << color.a << std::endl;
        
        SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));

        for(int i = 0; i < vertexCount-1; i++){
            SRE::Debug::drawLine(
                    glm::vec3(
                        vertices[i].x * Constants::METERS_TO_PIXELS,
                        vertices[i].y * Constants::METERS_TO_PIXELS,0), 
                    glm::vec3(
                        vertices[i+1].x * Constants::METERS_TO_PIXELS,
                        vertices[i+1].y * Constants::METERS_TO_PIXELS,0)
                    ); 
        }

        SRE::Debug::drawLine(glm::vec3(vertices[vertexCount-1].x * Constants::METERS_TO_PIXELS,vertices[vertexCount-1].y * Constants::METERS_TO_PIXELS,0), glm::vec3(vertices[0].x * Constants::METERS_TO_PIXELS,vertices[0].y * Constants::METERS_TO_PIXELS,0)); 
    }

    void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color) {
        DrawPolygon(vertices, vertexCount, color);
    }

    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
        const int size = 32;
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
        SRE::Debug::drawLine(glm::vec3(p1.x * Constants::METERS_TO_PIXELS,p1.y * Constants::METERS_TO_PIXELS,0), glm::vec3(p2.x * Constants::METERS_TO_PIXELS,p2.y * Constants::METERS_TO_PIXELS,0)); 
    }

    void DrawTransform(const b2Transform& xf) {}

    void DrawPoint(const b2Vec2& p, float size, const b2Color& color){
        DrawCircle(p, size, color);
    }


};
}
