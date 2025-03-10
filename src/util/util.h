#include <string>
#include <math.h>
#include <iostream>

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

#define NOMOUSE 0
#define LEFTMOUSE 1 << 0
#define RIGHTMOUSE 1 << 1
#define MIDDLEMOUSE 1 << 2


extern int global_width;
extern int global_height;

namespace lgui {
    namespace util {

        /**
         * @brief Colour is a struct that is used to store colour information
         * 
         */
        struct OldColour {
            unsigned short r, g, b, a;
            OldColour() {
                this->r = 0;
                this->g = 0;
                this->b = 0;
                this->a = 0;
            }
            OldColour(int r, int g, int b, int a) {
                this->r = (r * 65535) / 255;
                this->g = (g * 65535) / 255;
                this->b = (b * 65535) / 255;
                this->a = (a * 65535) / 255;
            }
        };

        struct Colour {
            float r, g, b, a;
            Colour() {
                this->r = 0;
                this->g = 0;
                this->b = 0;
                this->a = 0;
            }
            Colour(float r, float g, float b, float a) {
                this->r = r;
                this->g = g;
                this->b = b;
                this->a = a;
            }
        };

        struct Point {
            float x, y;
            float xtrue, ytrue;
            Point() {
                this->x = 0;
                this->y = 0;
                this->xtrue = 0;
                this->ytrue = 0;
            }
            Point(float x, float y) {
                this->xtrue = x;
                this->ytrue = y;
                this->x = x / global_width * 2 - 1;
                this->y = y / global_height * 2 - 1;
                this->y = -this->y;
            }
            bool operator==(const Point& other) const {
                return this->xtrue == other.xtrue && this->ytrue == other.ytrue;
            }

            bool operator!=(const Point& other) const {
                return this->xtrue != other.xtrue || this->ytrue != other.ytrue;
            }

            Point operator+(const Point& other) const {
                return Point(this->xtrue + other.xtrue, this->ytrue + other.ytrue);
            }

            Point operator-(const Point& other) const {
                return Point(this->xtrue - other.xtrue, this->ytrue - other.ytrue);
            }

            void Update() {
                this->x = this->xtrue / global_width * 2 - 1;
                this->y = this->ytrue / global_height * 2 - 1;
                this->y = -this->y;
            }

            void Rotate(float angle) {
                float ytrue = this->ytrue;
                float xtrue = this->xtrue;
                this->xtrue = xtrue * cos(angle) - ytrue * sin(angle);
                this->ytrue = xtrue * sin(angle) + ytrue * cos(angle);
                this->Update();
            }
        };

        /**
         * @brief StateInfo is a struct that is used to store information about certain states such as mouse press, mouse release, key press, key release and mouse position
         * 
         */
        struct StateInfo {
            Point position;
            int mousepress, mouserelease;
            bool keypress, keyrelease;
            int keycode;
            StateInfo() 
            {
                this->position = Point(0, 0);
                this->mousepress = NOMOUSE;
                this->mouserelease = NOMOUSE;
                this->keypress = false;
                this->keyrelease = false;
                this->keycode = 0;
            }
            StateInfo(Point position, int mousepress, int mouserelease, bool keypress, bool keyrelease, int keycode) {
                this->position = position;
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
            OldColour background_colour;
            WindowRequest() {
                this->type = NOTYPE;
                this->x = 0;
                this->y = 0;
                this->width = 0;
                this->height = 0;
                this->title = "";
                this->background_colour = OldColour(0, 0, 0, 0);
            }
            WindowRequest(int type, int x, int y, int width, int height, std::string title, OldColour background_colour) {
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
            Point position;
            float rotation;
            int width, height;
            OldColour colour;
            ObjectRequest() {
                this->type = NOCHANGE;
                this->position = Point(0, 0);
                this->rotation = 0;
                this->width = 0;
                this->height = 0;
                this->colour = OldColour(0, 0, 0, 0);
            }
            ObjectRequest(int type) {
                this->type = type;
                this->position = Point(0, 0);
                this->rotation = 0;
                this->width = 0;
                this->height = 0;
                this->colour = OldColour(0, 0, 0, 0);
            }
        };

        /**
         * @brief ClearArea is a struct that is used to store information about an area to clear
         * 
         */
        struct ClearArea {
            int x, y, width, height;
            ClearArea() {
                this->x = 0;
                this->y = 0;
                this->width = 0;
                this->height = 0;
            }
            ClearArea(int x, int y, int width, int height) {
                this->x = x;
                this->y = y;
                this->width = width;
                this->height = height;
            }
        };

        struct Transform {
            float x, y;
            float rotation;
            Transform() {
                this->x = 0;
                this->y = 0;
                this->rotation = 0;
            }
            Transform(float x, float y, float rotation) {
                this->x = x;
                this->y = y;
                this->rotation = rotation;
            }
        };
    }
}