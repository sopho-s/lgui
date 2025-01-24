#include "objects.h"

namespace lgui {
    namespace drawables {
        namespace objects {
            void oRectangle::draw(Display* display, Window& window, GC& gc) {
                this->rect->draw(display, window, gc);
            }

            std::vector<util::WindowRequest> oRectangle::update(float deltatime) {
                this->prevx = this->x;
                this->prevy = this->y;
                this->prevwidth = this->width;
                this->prevheight = this->height;
                this->prevfilled = this->filled;
                for (animations::Animation* animation : this->animations) {
                    util::ObjectRequest request = animation->update(deltatime);
                    if (request.type & UPDATEPOSITION) {
                        this->rect->x = request.x;
                        this->x = request.x;
                        this->rect->y = request.y;
                        this->y = request.y;
                        this->bound.set_position(request.x, request.y);
                    }
                }
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oRectangle::mouse_move(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oRectangle::mouse_press(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oRectangle::mouse_release(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oRectangle::key_press(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oRectangle::key_release(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            void oPNG::draw(Display* display, Window& window, GC& gc) {
                this->png->draw(display, window, gc);
            }

            std::vector<util::WindowRequest> oPNG::update(float deltatime) {
                this->prevx = this->x;
                this->prevy = this->y;
                this->prevwidth = this->width;
                this->prevheight = this->height;
                for (animations::Animation* animation : this->animations) {
                    util::ObjectRequest request = animation->update(deltatime);
                    if (request.type & UPDATEPOSITION) {
                        this->png->x = request.x;
                        this->x = request.x;
                        this->png->y = request.y;
                        this->y = request.y;
                        this->bound.set_position(request.x, request.y);
                    }
                }
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oPNG::mouse_move(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oPNG::mouse_press(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oPNG::mouse_release(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oPNG::key_press(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oPNG::key_release(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }
        }
    }
}