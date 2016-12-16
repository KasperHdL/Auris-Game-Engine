#pragma once

#include "Box2D/Box2D.h"
#include "SRE/Debug.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/constants.hpp>
#include <iostream>

#include "Auris/Constants.hpp"

namespace Auris{

//! The DebugDraw class that extend the b2Draw in box2D
    /*! Used to draw debug around everything
    */
class DebugDraw : public b2Draw{
public:

    //! The DebugDraw constructor.
        /*!
         * Does nothing.
        */
    DebugDraw(){}

    //! A DrawPolygon overload method, taking 3 arguments.
        /*! Draws a polygon on the screen using SimpleRenderEngine.
         * \param vertices a constant b2vec2 pointer. The vertices of the polygon.
         * \param vertexCount an int value. The vertex count of the polygon.
         * \param color a constant b2Color value. The color of the polygon.
         * \overload b2Draw::DrawPolygon()
        */
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

    //! A DrawSolidPolygon overload method, taking 3 arguments.
        /*! Draws a polygon using DrawPolygon method on the screen using SimpleRenderEngine.
         * \param vertices a constant b2vec2 pointer. The vertices of the polygon.
         * \param vertexCount an int value. The vertex count of the polygon.
         * \param color a constant b2Color value. The color of the polygon.
         * \overload b2Draw::DrawSolidPolygon()
        */
    void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color) {
        DrawPolygon(vertices, vertexCount, color);
    }

    //! A DrawCircle overload method, taking 3 arguments.
        /*! Draws a cicle using DrawPolygon method on the screen using SimpleRenderEngine.
         * \param center a constant b2vec2 pointer. The center of the circle.
         * \param radius a float value. The radius of the circle.
         * \param color a constant b2Color value. The color of the polygon.
         * \overload b2Draw::DrawCircle()
        */
    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
        const int size = 32;
        b2Vec2 array[size];

        for(int i = 0;i < size;i++){
            array[i] = center + b2Vec2(glm::cos(i * (2 * glm::pi<float>() / (float)size )) * radius, glm::sin(i * (2 * glm::pi<float>() / (float)size)) * radius);
        }

        DrawPolygon(&array[0], size, color);
    
    }

    //! A DrawSolidCircle overload method, taking 3 arguments.
        /*! Draws a cicle using DrawCircle method on the screen using SimpleRenderEngine.
         * \param center a constant b2vec2 pointer. The center of the circle.
         * \param radius a float value. The radius of the circle.
         * \param axis a b2vec2 pointer. Not used for anything.
         * \param color a constant b2Color value. The color of the polygon.
         * \overload b2Draw::DrawSolidCircle()
        */
    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
        DrawCircle(center, radius, color);

    }

    //! A DrawSegment overload method, taking 3 arguments.
        /*! Draws a line on the screen using SimpleRenderEngine.
         * \param p1 a constant b2vec2 pointer. First point of the line.
         * \param p2 a constant b2vec2 pointer. Second point of the line.
         * \param color a constant b2Color value. The color of the line.
         * \overload b2Draw::DrawSegment()
        */
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {

        SRE::Debug::setColor(glm::vec4(color.r, color.g, color.b, color.a));
        SRE::Debug::drawLine(glm::vec3(p1.x * Constants::METERS_TO_PIXELS,p1.y * Constants::METERS_TO_PIXELS,0), glm::vec3(p2.x * Constants::METERS_TO_PIXELS,p2.y * Constants::METERS_TO_PIXELS,0)); 
    }

    //! A DrawTransform overload method, taking 1 arguments.
        /*! Not used for anything
         * \param xf a constant b2Transform pointer. Not used for anything.
         * \overload b2Draw::DrawTransform()
        */
    void DrawTransform(const b2Transform& xf) {}


    //! A DrawPoint overload method, taking 3 arguments.
        /*! Draws a point using the DrawCircle method on the screen using SimpleRenderEngine.
         * \param p a constant b2vec2 pointer. The point to draw.
         * \param size a float value. The size of the point.
         * \param color a constant b2Color value. The color of the point.
         * \overload b2Draw::DrawPoint()
        */
    void DrawPoint(const b2Vec2& p, float size, const b2Color& color){
        DrawCircle(p, size, color);
    }


};
}
