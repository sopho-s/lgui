#include "objects.h"

namespace lgui {
    namespace drawables {
        namespace objects {
            void oTriangle::draw() {
                this->triangle->draw();
            }

            std::vector<util::WindowRequest> oTriangle::update(float deltatime) {
                this->prevp1 = this->p1;
                this->prevp2 = this->p2;
                this->prevp3 = this->p3;
                this->prevfilled = this->filled;
                for (animations::Animation* animation : this->animations) {
                    util::ObjectRequest request = animation->update(deltatime);
                    if (request.type & UPDATEPOSITION) {
                        util::Point p1diff = this->p1 - this->center;
                        util::Point p2diff = this->p2 - this->center;
                        util::Point p3diff = this->p3 - this->center;
                        this->center = request.position;
                        this->p1 = this->center + p1diff;
                        this->p2 = this->center + p2diff;
                        this->p3 = this->center + p3diff;
                        this->bound.set_position(request.position.x, request.position.y);
                    } else if (request.type & UPDATEROTATION) {
                        util::Point p1diff = this->p1 - this->center;
                        util::Point p2diff = this->p2 - this->center;
                        util::Point p3diff = this->p3 - this->center;
                        p1diff.Rotate(request.rotation);
                        p2diff.Rotate(request.rotation);
                        p3diff.Rotate(request.rotation);
                        this->p1 = this->center + p1diff;
                        this->p2 = this->center + p2diff;
                        this->p3 = this->center + p3diff;
                    }
                }
                this->triangle->p1 = this->p1;
                this->triangle->p2 = this->p2;
                this->triangle->p3 = this->p3;
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oTriangle::mouse_move(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oTriangle::mouse_press(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oTriangle::mouse_release(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oTriangle::key_press(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oTriangle::key_release(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            void oQuad::draw() {
                this->rect->draw();
            }

            std::vector<util::WindowRequest> oQuad::update(float deltatime) {
                this->prevp1 = this->p1;
                this->prevp2 = this->p2;
                this->prevp3 = this->p3;
                this->prevp4 = this->p4;
                this->prevfilled = this->filled;
                for (animations::Animation* animation : this->animations) {
                    util::ObjectRequest request = animation->update(deltatime);
                    if (request.type & UPDATEPOSITION) {
                    }
                }
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oQuad::mouse_move(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oQuad::mouse_press(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oQuad::mouse_release(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oQuad::key_press(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oQuad::key_release(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            void oRectangle::draw() {
                this->rect->draw();
            }

            std::vector<util::WindowRequest> oRectangle::update(float deltatime) {
                this->prevp1 = this->p1;
                this->prevp2 = this->p2;
                this->prevp3 = this->p3;
                this->prevp4 = this->p4;
                this->prevfilled = this->filled;
                for (animations::Animation* animation : this->animations) {
                    util::ObjectRequest request = animation->update(deltatime);
                    if (request.type & UPDATEPOSITION) {
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

            void oPNG::draw() {
                this->png->draw();
            }

            std::vector<util::WindowRequest> oPNG::update(float deltatime) {
                this->prevx = this->x;
                this->prevy = this->y;
                this->prevwidth = this->width;
                this->prevheight = this->height;
                for (animations::Animation* animation : this->animations) {
                    util::ObjectRequest request = animation->update(deltatime);
                    if (request.type & UPDATEPOSITION) {
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