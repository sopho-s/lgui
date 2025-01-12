#include "../drawables.h"
#include "../../util/util.h"
#include "bounds.h"
#include "animations/animations.h"
#include <X11/Xlib.h>
#include <cstdio>
#include <vector>
#pragma once

namespace lgui {
    namespace drawables {
        namespace objects {
            class Object {
            public:
                Object() {}
                virtual ~Object() {}
                virtual void draw(Display* display, Window& window, GC& gc) = 0;
                virtual void give_animation(animations::Animation* animation) = 0;
                virtual std::vector<util::WindowRequest> update(float deltatime) = 0;
                virtual std::vector<util::WindowRequest> mouse_move(util::StateInfo updateinfo) = 0;
                virtual std::vector<util::WindowRequest> mouse_press(util::StateInfo updateinfo) = 0;
                virtual std::vector<util::WindowRequest> mouse_release(util::StateInfo updateinfo) = 0;
                virtual std::vector<util::WindowRequest> key_press(util::StateInfo updateinfo) = 0;
                virtual std::vector<util::WindowRequest> key_release(util::StateInfo updateinfo) = 0;
            };

            class oRectangle : public Object {
            private:
                float x, y, width, height;
                util::Colour colour;
                bool filled;
                lRectangle* rect;
                RectangleBound bound;
                std::vector<animations::Animation*> animations;
            public:
                oRectangle() {}
                oRectangle(int x, int y, int width, int height, util::Colour colour, bool filled = true) {
                    this->x = (float)x;
                    this->y = (float)y;
                    this->width = width;
                    this->height = height;
                    this->colour = colour;
                    this->filled = filled;
                    this->rect = new lRectangle(x, y, width, height, colour, filled);
                    this->bound = RectangleBound(x, y, width, height);
                }
                void draw(Display* display, Window& window, GC& gc) override;
                void give_animation(animations::Animation* animation) override {
                    this->animations.push_back(animation);
                }
                virtual std::vector<util::WindowRequest> update(float deltatime);
                virtual std::vector<util::WindowRequest> mouse_move(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> mouse_press(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> mouse_release(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> key_press(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> key_release(util::StateInfo updateinfo);
            };

            class oPNG : public Object {
            private:
                float x, y, width, height;
                lPNGImage* png;
                RectangleBound bound;
                std::vector<animations::Animation*> animations;
            public:
                oPNG() {}
                oPNG(int x, int y, int width, int height, std::string image) {
                    this->x = (float)x;
                    this->y = (float)y;
                    this->width = width;
                    this->height = height;
                    this->png = new lPNGImage(x, y, image);
                    this->bound = RectangleBound(x, y, width, height);
                }
                void draw(Display* display, Window& window, GC& gc) override;
                void give_animation(animations::Animation* animation) override {
                    this->animations.push_back(animation);
                }
                virtual std::vector<util::WindowRequest> update(float deltatime);
                virtual std::vector<util::WindowRequest> mouse_move(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> mouse_press(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> mouse_release(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> key_press(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> key_release(util::StateInfo updateinfo);
            };
        }
    }
}