#include "../util/util.h"
#include "X11/Xlib.h"
#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "../drawables/drawables.h"
#include "../drawables/objects/objects.h"
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <map>
#include <algorithm>
#pragma once

namespace lgui {
    namespace window {
        /**
         * @brief A window class that used to create a window and draw objects on it
         * 
         */
        class lWindow {
            private:
                std::string title;
                int width, height;
                int x, y;
                util::OldColour old_background_colour;
                util::Colour background_colour;
                util::OldColour border_colour;
                XColor xbackground_colour;
                XColor xborder_colour;
                bool shown = false;
                int border_width;
                int black_colour;
                int white_colour;
                GLFWwindow* glwindow;
                Display* display;
                Window window;
                GC graphics_context;
                std::map<std::string, drawables::objects::Object*> objects;
            public:
                /**
                 * @brief Construct a new lWindow object
                 * 
                 */
                lWindow() {
                    glfwInit();
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
                    this->title = "";
                    this->x = 0;
                    this->y = 0;
                    this->width = 1;
                    this->height = 1;
                    this->old_background_colour = util::OldColour(0, 0, 0, 255);
                    this->background_colour = util::Colour(0, 0, 0, 255);
                    this->border_colour = util::OldColour(0, 0, 0, 255);
                    this->border_width = 0;
                }
                /**
                 * @brief Shows the window on the root screen
                 * 
                 */
                void show();
                /**
                 * @brief Hides the window
                 * 
                 */
                void hide();
                /**
                 * @brief Sets the title of the window
                 * 
                 * @param title The title of the window
                 */
                void set_title(const std::string& title);
                /**
                 * @brief Sets the size of the window
                 * 
                 * @param width The width of the window
                 * @param height The height of the window
                 */
                void set_size(int width, int height);
                /**
                 * @brief Sets the position of the window
                 * 
                 * @param x The x position of the window
                 * @param y The y position of the window
                 */
                void set_position(int x, int y);
                /**
                 * @brief Sets the border colour of the window
                 * 
                 * @param colour The border colour of the window
                 */
                void set_background_colour(const util::Colour& colour);
                void set_border_colour(const util::OldColour& colour);
                /**
                 * @brief Sets the border width of the window (DOES NOT WORK)
                 * 
                 * @param width The border width of the window
                 */
                void set_border_width(int width);
                /**
                 * @brief Sets the border radius of the window (DOES NOT WORK)
                 * 
                 * @param radius The border radius of the window
                 */
                void set_border_radius(int radius);
                /**
                 * @brief Refreshes the window (DOES NOT WORK)
                 * 
                 */
                void flush();
                /**
                 * @brief Clears the window
                 * 
                 */
                void clear();
                /**
                 * @brief Clears the window in certain areas
                 * 
                 * @param clearareas The areas to clear
                 */
                void clear(std::vector<util::ClearArea> clearareas);
                /**
                 * @brief Gets the events that have happened since the last call to this function
                 * 
                 * @return std::vector<XEvent> The events that have happened since the last call to this function
                 */
                std::vector<util::StateInfo> get_events();
                /**
                 * @brief Clears the events that have happened since the last call to get_events (DOES NOT WORK)
                 * 
                 */
                void clear_events();
                /**
                 * @brief Draws a drawable object on the window
                 * 
                 * @param drawable The drawable object to draw
                 */
                void draw(drawables::lDrawable& drawable);
                /**
                 * @brief Gets the font of the window
                 * 
                 * @return Font The font of the window
                 */
                Font get_font();
                /**
                 * @brief The main loop of the window
                 * 
                 * @param fps The frames per second of the window
                 */
                void main_loop(int fps);
                /**
                 * @brief Adds an object to the window
                 * 
                 * @param name The name of the object for reference
                 * @param object The object to add
                 */
                void add_object(std::string name, drawables::objects::Object* object);
        };
    }
}