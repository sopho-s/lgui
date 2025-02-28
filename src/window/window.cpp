#include <iostream>
#include "window.h"


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
            glViewport(0, 0, 800, 600);
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

        void lWindow::old_set_background_colour(const util::OldColour& colour) {
            
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
            printf("Flushing window\n");
        }

        void lWindow::clear() {
            // Clear window
            glClear(GL_COLOR_BUFFER_BIT);
            printf("Clearing window\n");
        }

        void lWindow::clear(std::vector<util::ClearArea> clearareas) {
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

        std::vector<XEvent> lWindow::get_events() {
            std::vector<XEvent> events = std::vector<XEvent>();
            return events;
        }

        void lWindow::clear_events() {
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
                std::vector<util::ClearArea> clearareas = std::vector<util::ClearArea>();
                for (auto const& pair: this->objects) {
                    std::vector<util::ClearArea> objectclearareas = pair.second->get_clear_areas();
                    for (util::ClearArea cleararea : objectclearareas) {
                        clearareas.push_back(cleararea);
                    }
                }
                auto end = std::chrono::high_resolution_clock::now();
                elapsed = end - start;
                deltatime = elapsed.count() / 1000000000.0;
                glfwGetFramebufferSize(this->glwindow, &width, &height);
                for (auto const& pair : this->objects) {
                    pair.second->update_viewport(this->x, this->y, this->width, this->height);
                    pair.second->update(deltatime);
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
                            this->old_set_background_colour(request.background_colour);
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
                /*for (XEvent e : this->get_events()) {
                    std::vector<util::WindowRequest> requests;
                    if (e.type == Expose) {
                        for (auto const& pair : this->objects) {
                            requests = pair.second->update(deltatime);
                        }
                        this->flush();
                    } else if (e.type == KeyPress) {
                        util::StateInfo updateinfo = util::StateInfo(e.xkey.x, e.xkey.y, false, false, true, false, e.xkey.keycode);
                        for (auto const& pair : this->objects) {
                            requests = pair.second->key_press(util::StateInfo(0, 0, false, false, true, false, e.xkey.keycode));
                        }
                    } else if (e.type == KeyRelease) {
                        util::StateInfo updateinfo = util::StateInfo(e.xkey.x, e.xkey.y, false, false, false, true, e.xkey.keycode);
                        for (auto const& pair : this->objects) {
                            requests = pair.second->key_release(util::StateInfo(0, 0, false, false, false, true, e.xkey.keycode));
                        }
                    } else if (e.type == ButtonPress) {
                        util::StateInfo updateinfo = util::StateInfo(e.xbutton.x, e.xbutton.y, true, false, false, false, e.xbutton.button);
                        for (auto const& pair : this->objects) {
                            requests = pair.second->mouse_press(util::StateInfo(e.xbutton.x, e.xbutton.y, true, false, false, false, e.xbutton.button));
                        }
                    } else if (e.type == ButtonRelease) {
                        util::StateInfo updateinfo = util::StateInfo(e.xbutton.x, e.xbutton.y, false, true, false, false, e.xbutton.button);
                        for (auto const& pair : this->objects) {
                            requests = pair.second->mouse_release(util::StateInfo(e.xbutton.x, e.xbutton.y, false, true, false, false, e.xbutton.button));
                        }
                    } else if (e.type == MotionNotify) {
                        util::StateInfo updateinfo = util::StateInfo(e.xmotion.x, e.xmotion.y, false, false, false, false, 0);
                        for (auto const& pair : this->objects) {
                            requests = pair.second->mouse_move(util::StateInfo(e.xmotion.x, e.xmotion.y, false, false, false, false, 0));
                        }
                    }
                    for (util::WindowRequest request : requests) {
                        if (request.type == NOTYPE) {
                            this->set_size(request.width, request.height);
                            this->set_position(request.x, request.y);
                            this->set_title(request.title);
                            this->old_set_background_colour(request.background_colour);
                        } else if (request.type == UPDATESIZE) {
                            this->set_size(request.width, request.height);
                        } else if (request.type == UPDATEPOSITION) {
                            this->set_position(request.x, request.y);
                        } else if (request.type == UPDATETITLE) {
                            this->set_title(request.title);
                        } else if (request.type == UPDATEBACKGROUNDCOLOUR) {
                            this->old_set_background_colour(request.background_colour);
                        } else if (request.type == UPDATEBORDERCOLOUR) {
                            ;
                        } else if (request.type == UPDATEBORDERWIDTH) {
                            ;
                        } else if (request.type == UPDATEBORDERRADIUS) {
                            ;
                        } else if (request.type == CLOSE) {
                            this->hide();
                            return;
                        }
                    }
                }*/
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