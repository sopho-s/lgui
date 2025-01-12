#include <X11/Xlib.h>
#include "../util/util.h"
#include <string>
#include <png.h>
#include <fstream>
#pragma once

namespace lgui {
    namespace drawables {
        class lDrawable {
            public:
                virtual void draw(Display* display, Window& window, GC& gc) = 0;
        };

        class lRectangle : public lDrawable {
            public:
                unsigned int x, y, width, height;
                util::Colour colour;
                bool filled;
                lRectangle(int x, int y, int width, int height, util::Colour colour, bool filled = true) {
                    this->x = x;
                    this->y = y;
                    this->width = width;
                    this->height = height;
                    this->colour = colour;
                    this->filled = filled;
                }
                void draw(Display* display, Window& window, GC& gc) override;
        };

        class lCircle : public lDrawable {
            public:
                unsigned int x, y, radius;
                util::Colour colour;
                bool filled;
                lCircle(int x, int y, int radius, util::Colour colour, bool filled = true) {
                    this->x = x;
                    this->y = y;
                    this->radius = radius;
                    this->colour = colour;
                    this->filled = filled;
                }
                void draw(Display* display, Window& window, GC& gc) override;
        };

        class lText : public lDrawable {
            public:
                unsigned int x, y;
                std::string text;
                util::Colour colour;
                XTextItem text_item;
                lText(int x, int y, std::string text, util::Colour colour, Font font = None) {
                    this->x = x;
                    this->y = y;
                    this->text = text;
                    this->colour = colour;
                    text_item.chars = (char*)text.c_str();
                    text_item.nchars = text.length();
                    text_item.delta = 0;
                    text_item.font = font;
                }
                void draw(Display* display, Window& window, GC& gc) override;
        };
        
        class lPNGImage : public lDrawable {
            public:
                unsigned int x, y, width, height;
                unsigned int true_width, true_height;
                std::string image_file;
                png_structp png;
                png_infop info;
                unsigned char** data;
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
                    *data = (unsigned char*)malloc(png_get_rowbytes(png, info) * (true_height));
                    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * (true_height));
                    for (int y = 0; y < height; y++) {
                        row_pointers[y] = *data + y * png_get_rowbytes(png, info);
                    }
                    png_read_image(png, row_pointers);
                    free(row_pointers);
                    png_destroy_read_struct(&png, &info, NULL);
                    fclose(file);
                }
                void draw(Display* display, Window& window, GC& gc) override;
        };
    }
}