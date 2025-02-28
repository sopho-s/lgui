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
            /**
             * @brief A base class for all objects
             * 
             */
            class Object {
            public:
                /**
                 * @brief Construct a new Object object
                 * 
                 */
                Object() {}
                /**
                 * @brief Destroy the Object object
                 * 
                 */
                virtual ~Object() {}
                /**
                 * @brief Draws the object on the window
                 * 
                 * @param display The display to draw on
                 * @param window The window to draw on
                 * @param gc The graphics context to draw with
                 */
                virtual void draw() = 0;
                /**
                 * @brief Gives an animation to the object
                 * 
                 * @param animation The animation to give
                 */
                virtual void give_animation(animations::Animation* animation) = 0;
                /**
                 * @brief Updates the object
                 * 
                 * @param deltatime The time since the last update
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> update(float deltatime) = 0;
                /**
                 * @brief Updates the object on mouse move
                 * 
                 * @param updateinfo The information about the mouse move
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> mouse_move(util::StateInfo updateinfo) = 0;
                /**
                 * @brief Updates the object on mouse press
                 * 
                 * @param updateinfo The information about the mouse press
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> mouse_press(util::StateInfo updateinfo) = 0;
                /**
                 * @brief Updates the object on mouse release
                 * 
                 * @param updateinfo The information about the mouse release
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> mouse_release(util::StateInfo updateinfo) = 0;
                /**
                 * @brief Updates the object on key press
                 * 
                 * @param updateinfo The information about the key press
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> key_press(util::StateInfo updateinfo) = 0;
                /**
                 * @brief Updates the object on key release
                 * 
                 * @param updateinfo The information about the key release
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> key_release(util::StateInfo updateinfo) = 0;
                /**
                 * @brief Gets the clear area of the object
                 * 
                 * @return util::ClearArea The clear area of the object
                 */
                virtual std::vector<util::ClearArea> get_clear_areas() = 0;

                virtual void update_viewport(int x, int y, int width, int height) = 0;
            };

            class oTriangle : public Object {
            private:
                util::Point center;
                util::Point p1, p2, p3;
                util::Point prevp1, prevp2, prevp3;
                util::OldColour colour;
                bool filled;
                bool prevfilled;
                lTriangle* triangle;
                TriangleBound bound;
                std::vector<animations::Animation*> animations;
            public:
                oTriangle() {}
                oTriangle(util::Point center, util::Point p1, util::Point p2, util::Point p3, util::OldColour colour, bool filled = true) {
                    this->center = center;
                    this->p1 = p1;
                    this->p2 = p2;
                    this->p3 = p3;
                    this->colour = colour;
                    this->filled = filled;
                    this->triangle = new lTriangle(p1, p2, p3, colour, filled);
                    this->bound = TriangleBound(p1, p2, p3);
                }
                void draw() override;
                void give_animation(animations::Animation* animation) override {
                    this->animations.push_back(animation);
                    printf("Added animation\n");
                }
                virtual std::vector<util::WindowRequest> update(float deltatime);
                virtual std::vector<util::WindowRequest> mouse_move(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> mouse_press(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> mouse_release(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> key_press(util::StateInfo updateinfo);
                virtual std::vector<util::WindowRequest> key_release(util::StateInfo updateinfo);
                virtual std::vector<util::ClearArea> get_clear_areas() override {
                    if (this->prevp1 != this->p1 || this->prevp2 != this->p2 || this->prevp3 != this->p3) {
                        return this->triangle->get_clear_areas();
                    }
                    return std::vector<util::ClearArea>();
                }
                virtual void update_viewport(int x, int y, int width, int height) {
                    this->triangle->update_viewport(x, y, width, height);
                    p1.Update(width, height);
                    p2.Update(width, height);
                    p3.Update(width, height);
                }
            };

            /**
             * @brief A rectangle object
             * 
             */
            class oQuad : public Object {
            private:
                util::Point p1, p2, p3, p4;
                util::Point prevp1, prevp2, prevp3, prevp4;
                util::OldColour colour;
                bool filled;
                bool prevfilled;
                lQuad* rect;
                RectangleBound bound;
                std::vector<animations::Animation*> animations;
            public:
                /**
                 * @brief Construct a new Rectangle object
                 * 
                 */
                oQuad() {}
                /**
                 * @brief Construct a new Rectangle object
                 * 
                 * @param p1 The first point of the rectangle
                 * @param p2 The second point of the rectangle
                 * @param p3 The third point of the rectangle
                 * @param p4 The fourth point of the rectangle
                 * @param colour The colour of the rectangle
                 * @param filled Whether the rectangle is filled or not
                 */
                oQuad(util::Point p1, util::Point p2, util::Point p3, util::Point p4, util::OldColour colour, bool filled = true) {
                    this->p1 = p1;
                    this->p2 = p2;
                    this->p3 = p3;
                    this->p4 = p4;
                    this->colour = colour;
                    this->filled = filled;
                    this->rect = new lQuad(p1, p2, p3, p4, colour, filled);
                    this->bound = RectangleBound();
                }
                /**
                 * @brief Draws the rectangle on the window
                 * 
                 * @param display The display to draw on
                 * @param window The window to draw on
                 * @param gc The graphics context to draw with
                 */
                void draw() override;
                /**
                 * @brief Gives an animation to the object
                 * 
                 * @param animation The animation to give
                 */
                void give_animation(animations::Animation* animation) override {
                    this->animations.push_back(animation);
                }
                /**
                 * @brief Updates the object
                 * 
                 * @param deltatime The time since the last update
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> update(float deltatime);
                /**
                 * @brief Updates the object on mouse move
                 * 
                 * @param updateinfo The information about the mouse move
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> mouse_move(util::StateInfo updateinfo);
                /**
                 * @brief Updates the object on mouse press
                 * 
                 * @param updateinfo The information about the mouse press
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> mouse_press(util::StateInfo updateinfo);
                /**
                 * @brief Updates the object on mouse release
                 * 
                 * @param updateinfo The information about the mouse release
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> mouse_release(util::StateInfo updateinfo);
                /**
                 * @brief Updates the object on key press
                 * 
                 * @param updateinfo The information about the key press
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> key_press(util::StateInfo updateinfo);
                /**
                 * @brief Updates the object on key release
                 * 
                 * @param updateinfo The information about the key release
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> key_release(util::StateInfo updateinfo);
                /**
                 * @brief Gets the clear area of the object
                 * 
                 * @return util::ClearArea The clear area of the object
                 */
                virtual std::vector<util::ClearArea> get_clear_areas() override {
                    return std::vector<util::ClearArea>();
                }
                virtual void update_viewport(int x, int y, int width, int height) {
                    this->rect->update_viewport(x, y, width, height);
                    p1.Update(width, height);
                    p2.Update(width, height);
                    p3.Update(width, height);
                    p4.Update(width, height);
                }
            };

            /**
             * @brief A PNG image object (DOES NOT WORK)
             * 
             */
            class oPNG : public Object {
            private:
                float x, y, width, height;
                float prevx, prevy, prevwidth, prevheight;
                lPNGImage* png;
                RectangleBound bound;
                std::vector<animations::Animation*> animations;
            public:
                /**
                 * @brief Construct a new PNG object
                 * 
                 */
                oPNG() {}
                /**
                 * @brief Construct a new PNG object
                 * 
                 * @param x The x position of the PNG image
                 * @param y The y position of the PNG image
                 * @param width The width of the PNG image
                 * @param height The height of the PNG image
                 * @param image The image file to load
                 */
                oPNG(int x, int y, int width, int height, std::string image) {
                    this->x = (float)x;
                    this->y = (float)y;
                    this->width = width;
                    this->height = height;
                    this->png = new lPNGImage(x, y, image);
                    this->bound = RectangleBound(x, y, width, height);
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
                 * @brief Gives an animation to the object
                 * 
                 * @param animation The animation to give
                 */
                void give_animation(animations::Animation* animation) override {
                    this->animations.push_back(animation);
                }
                /**
                 * @brief Updates the object
                 * 
                 * @param deltatime The time since the last update
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> update(float deltatime);
                /**
                 * @brief Updates the object on mouse move
                 * 
                 * @param updateinfo The information about the mouse move
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> mouse_move(util::StateInfo updateinfo);
                /**
                 * @brief Updates the object on mouse press
                 * 
                 * @param updateinfo The information about the mouse press
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> mouse_press(util::StateInfo updateinfo);
                /**
                 * @brief Updates the object on mouse release
                 * 
                 * @param updateinfo The information about the mouse release
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> mouse_release(util::StateInfo updateinfo);
                /**
                 * @brief Updates the object on key press
                 * 
                 * @param updateinfo The information about the key press
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> key_press(util::StateInfo updateinfo);
                /**
                 * @brief Updates the object on key release
                 * 
                 * @param updateinfo The information about the key release
                 * @return std::vector<util::WindowRequest> The requests to make to the window
                 */
                virtual std::vector<util::WindowRequest> key_release(util::StateInfo updateinfo);
                /**
                 * @brief Gets the clear area of the object
                 * 
                 * @return util::ClearArea The clear area of the object
                 */
                virtual std::vector<util::ClearArea> get_clear_areas() override {
                    if (this->prevx != this->prevy || this->prevwidth != this->width || this->prevheight != this->height) {
                        return this->png->get_clear_areas();
                    }
                    return std::vector<util::ClearArea>();
                }   
                virtual void update_viewport(int x, int y, int width, int height) {
                    this->png->update_viewport(x, y, width, height);
                    this->x = (float)x;
                    this->y = (float)y;
                    this->width = width;
                    this->height = height;
                }
            };
        }
    }
}