#include "../util/util.h"
#include "X11/Xlib.h"
#include <string>
#pragma

namespace lgui {
    namespace window {
        class lWindow {
            private:
                std::string title;
                int width, height;
                int x, y;
                util::Colour background_colour;
                util::Colour border_colour;
                XColor xbackground_colour;
                XColor xborder_colour;
                bool shown = false;
                int border_width;
                int black_colour;
                int white_colour;
                Display* display;
                Window window;
                GC graphics_context;
            public:
                lWindow() {
                    this->display = XOpenDisplay(NULL);
                    this->x = 0;
                    this->y = 0;
                    this->width = 0;
                    this->height = 0;
                    this->black_colour = BlackPixel(this->display, DefaultScreen(this->display));
                    this->white_colour = WhitePixel(this->display, DefaultScreen(this->display));
                    this->background_colour = util::Colour(0, 0, 0, 255);
                    this->border_colour = util::Colour(0, 0, 0, 255);
                    Colormap colormap = DefaultColormap(this->display, DefaultScreen(this->display));
                    this->xbackground_colour.red = this->background_colour.r;
                    this->xbackground_colour.green = this->background_colour.g;
                    this->xbackground_colour.blue = this->background_colour.b;
                    this->xbackground_colour.flags = DoRed | DoGreen | DoBlue;
                    XAllocColor(this->display, colormap, &this->xbackground_colour);
                    this->border_width = 0;
                }
                void show();
                void hide();
                void set_title(const std::string& title);
                void set_size(int width, int height) {
                    this->width = width;
                    this->height = height;
                }
                void set_position(int x, int y);
                void set_background_colour(const util::Colour& colour);
                void set_border_colour(const util::Colour& colour);
                void set_border_width(int width);
                void set_border_radius(int radius);
                void flush();
        };
    }
}