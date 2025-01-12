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
                virtual void draw(Display* display, Window& window, GC& gc) = 0;
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
            };

            /**
             * @brief A rectangle object
             * 
             */
            class oRectangle : public Object {
            private:
                float x, y, width, height;
                util::Colour colour;
                bool filled;
                lRectangle* rect;
                RectangleBound bound;
                std::vector<animations::Animation*> animations;
            public:
                /**
                 * @brief Construct a new Rectangle object
                 * 
                 */
                oRectangle() {}
                /**
                 * @brief Construct a new Rectangle object
                 * 
                 * @param x The x position of the rectangle
                 * @param y The y position of the rectangle
                 * @param width The width of the rectangle
                 * @param height The height of the rectangle
                 * @param colour The colour of the rectangle
                 * @param filled Whether the rectangle is filled or not
                 */
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
                /**
                 * @brief Draws the rectangle on the window
                 * 
                 * @param display The display to draw on
                 * @param window The window to draw on
                 * @param gc The graphics context to draw with
                 */
                void draw(Display* display, Window& window, GC& gc) override;
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
                    return this->rect->get_clear_areas();
                }
            };

            /**
             * @brief A PNG image object (DOES NOT WORK)
             * 
             */
            class oPNG : public Object {
            private:
                float x, y, width, height;
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
                void draw(Display* display, Window& window, GC& gc) override;
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
                    return this->png->get_clear_areas();
                }   
            };
        }
    }
}