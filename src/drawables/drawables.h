#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "../util/util.h"
#include <string>
#include <png.h>
#include <fstream>
#include <vector>
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
        };

        class lTriangle : public lDrawable {
            public:
                util::Point p1, p2, p3;
                util::OldColour colour;
                float timetest = 0;
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
                lTriangle(util::Point p1, util::Point p2, util::Point p3, util::OldColour colour, bool filled = true) {
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
        };

        /**
         * @brief A rectangle drawable object
         * 
         */
        class lRectangle : public lDrawable {
            public:
                unsigned int x, y, width, height;
                util::OldColour colour;
                bool filled;
                /**
                 * @brief Construct a new l Rectangle object
                 * 
                 * @param x The x position of the rectangle
                 * @param y The y position of the rectangle
                 * @param width The width of the rectangle
                 * @param height The height of the rectangle
                 * @param colour The colour of the rectangle
                 * @param filled Whether the rectangle is filled or not
                 */
                lRectangle(int x, int y, int width, int height, util::OldColour colour, bool filled = true) {
                    this->x = x;
                    this->y = y;
                    this->width = width;
                    this->height = height;
                    this->colour = colour;
                    this->filled = filled;
                }
                /**
                 * @brief Draws the rectangle on the window
                 * 
                 * @param display The display to draw on
                 * @param window The window to draw on
                 * @param gc The graphics context to draw with
                 */
                void draw() override;
                std::vector<util::ClearArea> get_clear_areas() override {
                    return std::vector<util::ClearArea> {util::ClearArea(x, y, width, height)};
                }
        };

        /**
         * @brief A circle drawable object
         * 
         */
        class lCircle : public lDrawable {
            public:
                unsigned int x, y, radius;
                util::OldColour colour;
                bool filled;
                /**
                 * @brief Construct a new l Circle object
                 * 
                 * @param x The x position of the circle
                 * @param y The y position of the circle
                 * @param radius The radius of the circle
                 * @param colour The colour of the circle
                 * @param filled Whether the circle is filled or not
                 */
                lCircle(int x, int y, int radius, util::OldColour colour, bool filled = true) {
                    this->x = x;
                    this->y = y;
                    this->radius = radius;
                    this->colour = colour;
                    this->filled = filled;
                }
                /**
                 * @brief Draws the circle on the window
                 * 
                 * @param display The display to draw on
                 * @param window The window to draw on
                 * @param gc The graphics context to draw with
                 */
                void draw() override;
                /**
                 * @brief Get the clear area object
                 * 
                 * @return util::ClearArea 
                 */
                std::vector<util::ClearArea> get_clear_areas() override {
                    return std::vector<util::ClearArea> {util::ClearArea(x - radius, y - radius, radius * 2, radius * 2)};
                }
        };

        /**
         * @brief A text drawable object
         * 
         */
        class lText : public lDrawable {
            public:
                unsigned int x, y;
                std::string text;
                util::OldColour colour;
                XTextItem text_item;
                /**
                 * @brief Construct a new l Text object
                 * 
                 * @param x The x position of the text
                 * @param y The y position of the text
                 * @param text The text to display
                 * @param colour The colour of the text
                 * @param font The font of the text
                 */
                lText(int x, int y, std::string text, util::OldColour colour, Font font = None) {
                    this->x = x;
                    this->y = y;
                    this->text = text;
                    this->colour = colour;
                    text_item.chars = (char*)text.c_str();
                    text_item.nchars = text.length();
                    text_item.delta = 0;
                    text_item.font = font;
                }
                /**
                 * @brief Draws the text on the window
                 * 
                 * @param display The display to draw on
                 * @param window The window to draw on
                 * @param gc The graphics context to draw with
                 */
                void draw() override;
                /**
                 * @brief Get the clear area object
                 * 
                 * @return util::ClearArea 
                 */
                std::vector<util::ClearArea> get_clear_areas() override {
                    return std::vector<util::ClearArea> {util::ClearArea(x, y, text.length() * 10, 10)};
                }
        };
        
        /**
         * @brief A PNG image drawable object (DOES NOT WORK)
         * 
         */
        class lPNGImage : public lDrawable {
            public:
                unsigned int x, y, width, height;
                unsigned int true_width, true_height;
                std::string image_file;
                png_structp png;
                png_infop info;
                png_bytep* data;
                XImage* image = nullptr;
                /**
                 * @brief Construct a new l PNG Image object
                 * 
                 * @param x The x position of the image
                 * @param y The y position of the image
                 * @param image The image file to display
                 */
                lPNGImage(int x, int y, std::string image) {
                    this->x = x;
                    this->y = y;
                    this->image_file = image;
                    FILE* file = fopen(image.c_str(), "rb");
                    if (!file) {
                        fprintf(stderr, "File %s could not be opened for reading\n", image.c_str());
                        return;
                    }
                    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
                    if (!png) {
                        fprintf(stderr, "png_create_read_struct failed\n");
                        fclose(file);
                        return;
                    }
                    info = png_create_info_struct(png);
                    if (!info) {
                        fprintf(stderr, "png_create_info_struct failed\n");
                        png_destroy_read_struct(&png, NULL, NULL);
                        fclose(file);
                        return;
                    }
                    png_init_io(png, file);
                    png_read_info(png, info);

                    true_width = png_get_image_width(png, info);
                    true_height = png_get_image_height(png, info);
                    width = true_width;
                    height = true_height;
                    size_t bytesrow = png_get_rowbytes(png, info);
                    size_t totalsize = bytesrow * true_height;
                    data = (png_bytep*)malloc(totalsize);
                    for (int i = 0; i < true_height; i++) {
                        data[i] = (png_bytep)malloc(png_get_rowbytes(png, info));
                    }
                    png_read_image(png, data);
                    fclose(file);
                }
                /**
                 * @brief Draws the PNG image on the window
                 * 
                 * @param display The display to draw on
                 * @param window The window to draw on
                 * @param gc The graphics context to draw with
                 */
                void draw() override;
                /**
                 * @brief Get the clear area object
                 * 
                 * @return util::ClearArea 
                 */
                std::vector<util::ClearArea> get_clear_areas() override {
                    return std::vector<util::ClearArea> {util::ClearArea(0, 0, 1, 1)};
                }
        };
    }
}