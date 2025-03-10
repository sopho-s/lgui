#include <iostream>
#include "window.h"


int global_width = 0;
int global_height = 0;

std::vector<lgui::util::StateInfo> interactions = std::vector<lgui::util::StateInfo>();

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    lgui::util::StateInfo info = lgui::util::StateInfo(lgui::util::Point(xpos, ypos), NOMOUSE, NOMOUSE, false, false, 0);
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            info.mousepress = LEFTMOUSE;
        } else if (action == GLFW_RELEASE) {
            info.mouserelease = LEFTMOUSE;
        }
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            info.mousepress = RIGHTMOUSE;
        } else if (action == GLFW_RELEASE) {
            info.mouserelease = RIGHTMOUSE;
        }
    } else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        if (action == GLFW_PRESS) {
            info.mousepress = MIDDLEMOUSE;
        } else if (action == GLFW_RELEASE) {
            info.mouserelease = MIDDLEMOUSE;
        }
    }
    interactions.push_back(info);
}

void GLAPIENTRY openglDebugCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* message, const void* userParam) {
    std::cout << "OpenGL Debug Message (" << id << "): " << message << std::endl;

    // Log additional info based on severity
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:         std::cerr << "Severity: HIGH\n"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       std::cerr << "Severity: MEDIUM\n"; break;
    case GL_DEBUG_SEVERITY_LOW:          std::cerr << "Severity: LOW\n"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: NOTIFICATION\n"; break;
    }

    // Breakpoint in debug mode for severe errors
    if (severity == GL_DEBUG_SEVERITY_HIGH) {
        std::cerr << "Critical error, breaking execution!\n";
        __builtin_trap(); // For Visual Studio (use `__builtin_trap()` for GCC/Clang)
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    global_width = width;
    global_height = height;
    glViewport(0, 0, width, height);
}

namespace lgui {
    namespace window {
        void lWindow::show() {
            this->glwindow = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
            glfwMakeContextCurrent(this->glwindow);
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                fprintf(stderr, "Failed to initialize GLAD\n");
            }
            glfwSetFramebufferSizeCallback(this->glwindow, framebuffer_size_callback);
            glfwSetMouseButtonCallback(this->glwindow, mouse_button_callback);
            global_width = this->width;
            global_height = this->height;
            glViewport(0, 0, this->width, this->height);
            glClearColor(this->background_colour.r, this->background_colour.g, this->background_colour.b, this->background_colour.a);
            glClear(GL_COLOR_BUFFER_BIT);
            this->shown = true;
            glDisable(GL_CULL_FACE);



            std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
            std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
            std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
            std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        }

        void lWindow::hide() {
            glfwSetWindowShouldClose(this->glwindow, true);
            this->shown = false;
        }

        void lWindow::set_background_colour(const util::Colour& colour) {
            // Set background colour
            this->background_colour.a = colour.a;
            this->background_colour.r = colour.r;
            this->background_colour.g = colour.g;
            this->background_colour.b = colour.b;
            if (this->shown) {
                glClearColor(this->background_colour.r, this->background_colour.g, this->background_colour.b, this->background_colour.a);
            }
        }
        
        void lWindow::flush() {
            glfwPollEvents();
            glfwSwapBuffers(this->glwindow);
        }

        void lWindow::clear() {
            // Clear window
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void lWindow::set_title(const std::string& title) {
            this->title = title;
        }

        void lWindow::set_size(int width, int height) {
            this->width = width;
            this->height = height;
        } 

        void lWindow::set_position(int x, int y) {
            this->x = x;
            this->y = y;
        } 

        std::vector<util::StateInfo> lWindow::get_events() {
            std::vector<util::StateInfo> events = std::vector<util::StateInfo>(interactions.size());
            std::copy(interactions.begin(), interactions.end(), events.begin());
            interactions.clear();
            return events;
        }

        void lWindow::draw(drawables::lDrawable& drawable) {
            drawable.draw();
            std::cout << "test" << std::endl;
        }

        Font lWindow::get_font() {
            return Font();
        }

        void lWindow::main_loop(int fps) {
            float time = 1.0 / fps;
            float deltatime = 0;
            auto start = std::chrono::high_resolution_clock::now();
            for(;;) {
                auto enddiff = std::chrono::high_resolution_clock::now();
                auto elapsed = enddiff - start;
                float waitedtime = elapsed.count() / 1000000000.0;
                if (waitedtime < time) {
                    std::this_thread::sleep_for(std::chrono::duration<float>(time - waitedtime));
                }
                auto end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                deltatime = elapsed.count() / 1000000000.0;
                std::vector<util::StateInfo> events = this->get_events();
                glfwGetFramebufferSize(this->glwindow, &width, &height);
                for (auto const& pair : this->objects) {
                    pair.second->update_viewport(this->x, this->y);
                    pair.second->update(deltatime);
                    for (util::StateInfo event : events) {
                        if (event.mousepress) {
                            pair.second->mouse_press(event);
                        } else if (event.mouserelease) {
                            pair.second->mouse_release(event);
                        } else if (event.keypress) {
                            pair.second->key_press(event);
                        } else if (event.keyrelease) {
                            pair.second->key_release(event);
                        }
                    }
                }
                for (auto const& pair : this->objects) {
                    std::vector<util::WindowRequest> requests = pair.second->update(deltatime);
                    for (util::WindowRequest request : requests) {
                        if (request.type & UPDATESIZE) {
                            this->set_size(request.width, request.height);
                        } else if (request.type & UPDATEPOSITION) {
                            this->set_position(request.x, request.y);
                        } else if (request.type & UPDATETITLE) {
                            this->set_title(request.title);
                        } else if (request.type & UPDATEBACKGROUNDCOLOUR) {
                            ;
                        } else if (request.type & UPDATEBORDERCOLOUR) {
                            ;
                        } else if (request.type & UPDATEBORDERWIDTH) {
                            ;
                        } else if (request.type & UPDATEBORDERRADIUS) {
                            ;
                        } else if (request.type & CLOSE) {
                            this->hide();
                            return;
                        }
                    }
                }
                start = std::chrono::high_resolution_clock::now();
                this->clear();
                for (auto const& pair : this->objects) {
                    pair.second->draw();
                }
                this->flush();
                if (glfwWindowShouldClose(this->glwindow)) {
                    glfwDestroyWindow(this->glwindow);
                    glfwTerminate();
                    break;
                }
            }
        }

        void lWindow::add_object(std::string name, drawables::objects::Object* object) {
            this->objects[name] = object;
        }
    }
}