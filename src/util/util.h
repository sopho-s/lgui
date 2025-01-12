#include <string>
#pragma once

#define NOTYPE 1 << 0
#define UPDATESIZE 1 << 1
#define UPDATEPOSITION 1 << 2
#define UPDATETITLE 1 << 2
#define UPDATEBACKGROUNDCOLOUR 1 << 4
#define UPDATEBORDERCOLOUR 1 << 5
#define UPDATEBORDERWIDTH 1 << 6
#define UPDATEBORDERRADIUS 1 << 7
#define CLOSE 1 << 8

#define NOCHANGE 1 << 0
#define UPDATESIZE 1 << 1
#define UPDATEPOSITION 1 << 2
#define UPDATEROTATION 1 << 3
#define UPDATECOLOUR 1 << 4

namespace lgui {
    namespace util {
        struct Colour {
            unsigned short r, g, b, a;
            Colour() {
                this->r = 0;
                this->g = 0;
                this->b = 0;
                this->a = 0;
            }
            Colour(int r, int g, int b, int a) {
                this->r = r;
                this->g = g;
                this->b = b;
                this->a = a;
            }
        };

        struct StateInfo {
            int x, y;
            bool mousepress, mouserelease;
            bool keypress, keyrelease;
            int keycode;
            StateInfo() {
                this->x = 0;
                this->y = 0;
                this->mousepress = false;
                this->mouserelease = false;
                this->keypress = false;
                this->keyrelease = false;
                this->keycode = 0;
            }
            StateInfo(int x, int y, bool mousepress, bool mouserelease, bool keypress, bool keyrelease, int keycode) {
                this->x = x;
                this->y = y;
                this->mousepress = mousepress;
                this->mouserelease = mouserelease;
                this->keypress = keypress;
                this->keyrelease = keyrelease;
                this->keycode = keycode;
            }
        };

        struct WindowRequest {
            int type;
            int x, y;
            int width, height;
            std::string title;
            Colour background_colour;
            WindowRequest() {
                this->type = NOTYPE;
                this->x = 0;
                this->y = 0;
                this->width = 0;
                this->height = 0;
                this->title = "";
                this->background_colour = Colour(0, 0, 0, 0);
            }
            WindowRequest(int type, int x, int y, int width, int height, std::string title, Colour background_colour) {
                this->type = type;
                this->x = x;
                this->y = y;
                this->width = width;
                this->height = height;
                this->title = title;
                this->background_colour = background_colour;
            }
        };

        struct ObjectRequest {
            int type;
            float x, y;
            float rotation;
            int width, height;
            Colour colour;
            ObjectRequest() {
                this->type = NOCHANGE;
                this->x = 0;
                this->y = 0;
                this->rotation = 0;
                this->width = 0;
                this->height = 0;
                this->colour = Colour(0, 0, 0, 0);
            }
            ObjectRequest(int type) {
                this->type = type;
                this->x = 0;
                this->y = 0;
                this->rotation = 0;
                this->width = 0;
                this->height = 0;
                this->colour = Colour(0, 0, 0, 0);
            }
        };
    }
}