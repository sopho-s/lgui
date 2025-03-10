#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "../util/util.h"
#include <string>
#include <png.h>
#include <fstream>
#include <vector>
#include <iostream>
#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <math.h>
#pragma once

namespace lgui {
    namespace drawables {
        /**
         * @brief A base class for all drawable objects
         * 
         */
        class lDrawable {
            public:
                /**
                 * @brief Draws the object on the window
                 * 
                 * @param display The display to draw on
                 * @param window The window to draw on
                 * @param gc The graphics context to draw with
                 */
                virtual void draw() = 0;
                virtual std::vector<util::ClearArea> get_clear_areas() = 0;
                virtual void update_viewport(int x, int y) = 0;
        };

        class lTriangle : public lDrawable {
            public:
                util::Point p1, p2, p3;
                util::Colour colour;
                bool filled;
                const char* vertexShaderSource = "#version 330 core\n"
                "layout (location = 0) in vec2 aPos;\n"
                "void main() {\n"
                "    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                "}\0";
                const char* fragmentShaderSource = "#version 330 core\n"
                "out vec4 FragColour;\n"
                "uniform vec4 triColour;\n"
                "void main() {\n"
                "    FragColour = triColour;\n"
                "}\0";
                unsigned int shaderProgram;
                float vertices[6] = {
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f
                };
                unsigned int VBO, VAO;
                /**
                 * @brief Construct a new l Triangle object
                 * 
                 * @param p1 The first point of the triangle
                 * @param p2 The second point of the triangle
                 * @param p3 The third point of the triangle
                 * @param colour The colour of the triangle
                 * @param filled Whether the triangle is filled or not
                 */
                lTriangle(util::Point p1, util::Point p2, util::Point p3, util::Colour colour, bool filled = true) {
                    this->p1 = p1;
                    this->p2 = p2;
                    this->p3 = p3;
                    this->colour = colour;
                    this->filled = filled;
                    init();
                }
                void init();
                /**
                 * @brief Draws the triangle on the window
                 * 
                 * @param display The display to draw on
                 * @param window The window to draw on
                 * @param gc The graphics context to draw with
                 */
                void draw() override;

                std::vector<util::ClearArea> get_clear_areas() override {
                    return std::vector<util::ClearArea> {util::ClearArea(p1.x, p1.y, p2.x, p2.y), util::ClearArea(p2.x, p2.y, p3.x, p3.y), util::ClearArea(p3.x, p3.y, p1.x, p1.y)};
                }

                void update_viewport(int x, int y) override {
                    p1.Update();
                    p2.Update();
                    p3.Update();
                }
        };

        /**
         * @brief A rectangle drawable object
         * 
         */
        class lQuad : public lDrawable {
            public:
                util::Point p1, p2, p3, p4;
                util::Colour colour;
                const char* vertexShaderSource = "#version 330 core\n"
                "layout (location = 0) in vec2 aPos;\n"
                "void main() {\n"
                "    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                "}\0";
                const char* fragmentShaderSource = "#version 330 core\n"
                "out vec4 FragColour;\n"
                "uniform vec4 triColour;\n"
                "void main() {\n"
                "    FragColour = triColour;\n"
                "}\0";
                unsigned int shaderProgram;
                float vertices[8] = {
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f,
                    0.0f, 0.0f
                };
                int indices[6] = {
                    0, 1, 2,
                    2, 3, 0
                };
                unsigned int VBO, VAO, EBO;
                bool filled;
                /**
                 * @brief Construct a new l Quad object
                 * 
                 * @param p1 The first point of the quad
                 * @param p2 The second point of the quad
                 * @param p3 The third point of the quad
                 * @param p4 The fourth point of the quad
                 * @param colour The colour of the quad
                 * @param filled Whether the quad is filled or not
                 */
                lQuad(util::Point p1, util::Point p2, util::Point p3, util::Point p4, util::Colour colour, bool filled = true) {
                    this->p1 = p1;
                    this->p2 = p2;
                    this->p3 = p3;
                    this->p4 = p4;
                    this->colour = colour;
                    this->filled = filled;
                    init();
                }
                void init();
                /**
                 * @brief Draws the rectangle on the window
                 * 
                 * @param display The display to draw on
                 * @param window The window to draw on
                 * @param gc The graphics context to draw with
                 */
                void draw() override;
                std::vector<util::ClearArea> get_clear_areas() override {
                    return std::vector<util::ClearArea> {util::ClearArea()};
                }

                void update_viewport(int x, int y) override {
                    p1.Update();
                    p2.Update();
                    p3.Update();
                    p4.Update();
                }
        };
    }
}