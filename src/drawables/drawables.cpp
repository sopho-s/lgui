#include "drawables.h"
namespace lgui {
    namespace drawables {
        void lRectangle::draw(Display* display, Window& window, GC& gc) {
            XColor draw_colour;
            Colormap colourmap = DefaultColormap(display, DefaultScreen(display));
            draw_colour.red = this->colour.r;
            draw_colour.green = this->colour.g;
            draw_colour.blue = this->colour.b;
            draw_colour.flags = DoRed | DoGreen | DoBlue;
            if (!XAllocColor(display, colourmap, &draw_colour)) {
                return;
            }
            XSetForeground(display, gc, draw_colour.pixel);
            XSetLineAttributes(display, gc, 1, LineSolid, CapButt, JoinBevel);
            XSetFillStyle(display, gc, FillSolid);
            if (this->filled) {
                XFillRectangle(display, window, gc, x, y, (unsigned int)width, (unsigned int)height);
            } else {
                XDrawRectangle(display, window, gc, x, y, (unsigned int)width, (unsigned int)height);
            }
        }

        void lCircle::draw(Display* display, Window& window, GC& gc) {
            XColor draw_colour;
            Colormap colourmap = DefaultColormap(display, DefaultScreen(display));
            draw_colour.red = this->colour.r;
            draw_colour.green = this->colour.g;
            draw_colour.blue = this->colour.b;
            draw_colour.flags = DoRed | DoGreen | DoBlue;
            if (!XAllocColor(display, colourmap, &draw_colour)) {
                return;
            }
            XSetForeground(display, gc, draw_colour.pixel);
            XSetLineAttributes(display, gc, 1, LineSolid, CapButt, JoinBevel);
            XSetFillStyle(display, gc, FillSolid);
            if (this->filled) {
                XFillArc(display, window, gc, x - radius, y - radius, radius * 2, radius * 2, 0, 360 * 64);
            } else {
                XDrawArc(display, window, gc, x - radius, y - radius, radius * 2, radius * 2, 0, 360 * 64);
            }
        }

        void lText::draw(Display* display, Window& window, GC& gc) {
            XColor draw_colour;
            Colormap colourmap = DefaultColormap(display, DefaultScreen(display));
            draw_colour.red = this->colour.r;
            draw_colour.green = this->colour.g;
            draw_colour.blue = this->colour.b;
            draw_colour.flags = DoRed | DoGreen | DoBlue;
            if (!XAllocColor(display, colourmap, &draw_colour)) {
                return;
            }
            XSetForeground(display, gc, draw_colour.pixel);
            XDrawText(display, window, gc, x, y, &text_item, 1);
        }

        void lPNGImage::draw(Display* display, Window& window, GC& gc) {
            XImage* image = XCreateImage(display, DefaultVisual(display, DefaultScreen(display)), 24, ZPixmap, 0, (char*)data, width, height, 32, 0);
            XPutImage(display, window, gc, image, 0, 0, x, y, width, height);
        }
    }
}