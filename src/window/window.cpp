#include <iostream>
#include "window.h"

namespace lgui {
    namespace window {
        void lWindow::show() {
            // Show the window
            this->window = XCreateSimpleWindow(this->display, DefaultRootWindow(this->display), this->x, this->y, this->width, this->height, this->border_width, this->white_colour, this->xbackground_colour.pixel);
            if (this->title != "") {
                XStoreName(this->display, this->window, this->title.c_str());
            }
            XSelectInput(this->display, window, StructureNotifyMask | ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | Button1MotionMask | Button2MotionMask | Button3MotionMask | Button4MotionMask | Button5MotionMask | KeyReleaseMask | EnterWindowMask | LeaveWindowMask | FocusChangeMask | PropertyChangeMask | VisibilityChangeMask | ColormapChangeMask | OwnerGrabButtonMask | ResizeRedirectMask | SubstructureRedirectMask  | ButtonMotionMask | KeymapStateMask | ResizeRedirectMask);
            XMapWindow(this->display, window);
            this->graphics_context = XCreateGC(this->display, this->window, 0, NULL);
            for(;;) {
                XEvent e;
                XNextEvent(this->display, &e);
                if (e.type == MapNotify) {
                    break;
                }
            }
            XFlush(this->display);
            this->shown = true;
        }

        void lWindow::hide() {
            // Hide the window
            XUnmapWindow(this->display, this->window);
            XFlush(this->display);
            this->window = Window();
            this->graphics_context = GC();
            this->shown = false;
        }

        void lWindow::set_background_colour(const util::Colour& colour) {
            // Set background colour
            this->background_colour.a = colour.a;
            this->background_colour.r = colour.r;
            this->background_colour.g = colour.g;
            this->background_colour.b = colour.b;
            Colormap colourmap = DefaultColormap(this->display, DefaultScreen(this->display));
            this->xbackground_colour.red = this->background_colour.r;
            this->xbackground_colour.green = this->background_colour.g;
            this->xbackground_colour.blue = this->background_colour.b;
            this->xbackground_colour.flags = DoRed | DoGreen | DoBlue;
            XAllocColor(this->display, colourmap, &this->xbackground_colour);
            if (this->shown) {
                XSetWindowBackground(this->display, this->window, this->xbackground_colour.pixel);
            }
        }
        
        void lWindow::flush() {
            // Refresh window
            XFlush(this->display);
        }

        void lWindow::clear() {
            // Clear window
            XClearWindow(this->display, this->window);
        }

        void lWindow::clear(std::vector<util::ClearArea> clearareas) {
            // Clear window in certain areas
            for (util::ClearArea cleararea : clearareas) {
                XClearArea(this->display, this->window, cleararea.x, cleararea.y, cleararea.width, cleararea.height, false);
            }
        }

        void lWindow::set_title(const std::string& title) {
            this->title = title;
            if (this->shown) {
                XStoreName(this->display, this->window, this->title.c_str());
            }
        }

        void lWindow::set_size(int width, int height) {
            this->width = width;
            this->height = height;
            if (this->shown) {
                XResizeWindow(this->display, this->window, this->width, this->height);
            }
        } 

        void lWindow::set_position(int x, int y) {
            this->x = x;
            this->y = y;
            if (this->shown) {
                XMoveWindow(this->display, this->window, this->x, this->y);
            }
        } 

        std::vector<XEvent> lWindow::get_events() {
            std::vector<XEvent> events = std::vector<XEvent>();
            while (XPending(this->display)) {
                XEvent e;
                XNextEvent(this->display, &e);
                events.push_back(e);
            }
            return events;
        }

        void lWindow::clear_events() {
            while (XPending(this->display)) {
                XEvent e;
                XNextEvent(this->display, &e);
            }
        }

        void lWindow::draw(drawables::lDrawable& drawable) {
            drawable.draw(this->display, this->window, this->graphics_context);
            std::cout << "test" << std::endl;
        }

        Font lWindow::get_font() {
            return XLoadFont(this->display, "fixed");
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
                            this->set_background_colour(request.background_colour);
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
                for (XEvent e : this->get_events()) {
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
                            this->set_background_colour(request.background_colour);
                        } else if (request.type == UPDATESIZE) {
                            this->set_size(request.width, request.height);
                        } else if (request.type == UPDATEPOSITION) {
                            this->set_position(request.x, request.y);
                        } else if (request.type == UPDATETITLE) {
                            this->set_title(request.title);
                        } else if (request.type == UPDATEBACKGROUNDCOLOUR) {
                            this->set_background_colour(request.background_colour);
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
                }
                this->clear(clearareas);
                for (auto const& pair : this->objects) {
                    pair.second->draw(this->display, this->window, this->graphics_context);
                }
                this->flush();
                XSync(this->display, true);
            }
        }

        void lWindow::add_object(std::string name, drawables::objects::Object* object) {
            this->objects[name] = object;
        }
    }
}