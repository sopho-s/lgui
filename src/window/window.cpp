#include "window.h"

namespace lgui {
    namespace window {
        void lWindow::show() {
            // Show the window
            this->window = XCreateSimpleWindow(this->display, DefaultRootWindow(this->display), this->x, this->y, this->width, this->height, this->border_width, this->white_colour, this->xbackground_colour.pixel);
            XSelectInput(this->display, window, StructureNotifyMask);
            XMapWindow(this->display, window);
            this->graphics_context = XCreateGC(this->display, this->window, 0, NULL);
            XSetForeground(this->display, this->graphics_context, this->xbackground_colour.pixel);
            for(;;) {
                XEvent e;
                XNextEvent(this->display, &e);
                if (e.type == MapNotify)
                break;
            }
            XFlush(this->display);
            this->shown = true;
        }
        void lWindow::hide() {
            // Hide the window
            XUnmapWindow(this->display, this->window);
            XFlush(this->display);
            this->window = Window();
            this->graphics_context = GC();
            this->shown = false;
        }

        void lWindow::set_background_colour(const util::Colour& colour) {
            this->background_colour.a = colour.a;
            this->background_colour.r = colour.r;
            this->background_colour.g = colour.g;
            this->background_colour.b = colour.b;
            Colormap colourmap = DefaultColormap(this->display, DefaultScreen(this->display));
            this->xbackground_colour.red = this->background_colour.r;
            this->xbackground_colour.green = this->background_colour.g;
            this->xbackground_colour.blue = this->background_colour.b;
            this->xbackground_colour.flags = DoRed | DoGreen | DoBlue;
            XAllocColor(this->display, colourmap, &this->xbackground_colour);
            if (this->shown) {
                XSetWindowBackground(this->display, this->window, this->xbackground_colour.pixel);
            }
        }
        
        void lWindow::flush() {
            XClearWindow(this->display, this->window);
            XFlush(this->display);
        }
    }
}