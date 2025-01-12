#include <string>
#pragma once

#define UPDATESIZE 1 << 0
#define UPDATEPOSITION 1 << 1
#define UPDATETITLE 1 << 2
#define UPDATEBACKGROUNDCOLOUR 1 << 3
#define UPDATEBORDERCOLOUR 1 << 4
#define UPDATEBORDERWIDTH 1 << 5
#define UPDATEBORDERRADIUS 1 << 6
#define NOTYPE UPDATESIZE | UPDATEPOSITION | UPDATETITLE | UPDATEBACKGROUNDCOLOUR | UPDATEBORDERCOLOUR | UPDATEBORDERWIDTH | UPDATEBORDERRADIUS
#define CLOSE 1 << 7

#define NOCHANGE 0
#define UPDATESIZE 1 << 0
#define UPDATEPOSITION 1 << 1
#define UPDATEROTATION 1 << 2
#define UPDATECOLOUR 1 << 3
#define ALLCHANGES UPDATESIZE | UPDATEPOSITION | UPDATEROTATION | UPDATECOLOUR

namespace lgui {
    namespace util {

        /**
         * @brief Colour is a struct that is used to store colour information
         * 
         */
        struct Colour {
            unsigned short r, g, b, a;
            Colour() {
                this->r = 0;
                this->g = 0;
                this->b = 0;
                this->a = 0;
            }
            Colour(int r, int g, int b, int a) {
                this->r = (r * 65535) / 255;
                this->g = (g * 65535) / 255;
                this->b = (b * 65535) / 255;
                this->a = (a * 65535) / 255;
            }
        };

        /**
         * @brief StateInfo is a struct that is used to store information about certain states such as mouse press, mouse release, key press, key release and mouse position
         * 
         */
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

        /**
         * @brief WindowRequest is a struct that is used to request changes to a window
         * 
         */
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

        /**
         * @brief ObjectRequest is a struct that is used to request changes to an object
         * 
         */
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