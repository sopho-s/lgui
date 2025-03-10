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
                        this->bound.set_position(request.position);
                        this->bound.set_points(this->p1, this->p2, this->p3);
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
                        this->bound.set_points(this->p1, this->p2, this->p3);
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
                        util::Point p1diff = this->p1 - this->center;
                        util::Point p2diff = this->p2 - this->center;
                        util::Point p3diff = this->p3 - this->center;
                        util::Point p4diff = this->p4 - this->center;
                        this->center = request.position;
                        this->p1 = this->center + p1diff;
                        this->p2 = this->center + p2diff;
                        this->p3 = this->center + p3diff;
                        this->p4 = this->center + p4diff;
                        this->bound1.set_position(request.position);
                        this->bound1.set_points(this->p1, this->p2, this->p3);
                        this->bound2.set_position(request.position);
                        this->bound2.set_points(this->p3, this->p4, this->p1);
                    } else if (request.type & UPDATEROTATION) {
                        util::Point p1diff = this->p1 - this->center;
                        util::Point p2diff = this->p2 - this->center;
                        util::Point p3diff = this->p3 - this->center;
                        util::Point p4diff = this->p4 - this->center;
                        p1diff.Rotate(request.rotation);
                        p2diff.Rotate(request.rotation);
                        p3diff.Rotate(request.rotation);
                        p4diff.Rotate(request.rotation);
                        this->p1 = this->center + p1diff;
                        this->p2 = this->center + p2diff;
                        this->p3 = this->center + p3diff;
                        this->p4 = this->center + p4diff;
                        this->bound1.set_points(this->p1, this->p2, this->p3);
                        this->bound2.set_points(this->p3, this->p4, this->p1);
                    }
                }
                this->rect->p1 = this->p1;
                this->rect->p2 = this->p2;
                this->rect->p3 = this->p3;
                this->rect->p4 = this->p4;
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oQuad::mouse_move(util::StateInfo updateinfo) {
                return std::vector<util::WindowRequest>();
            }

            std::vector<util::WindowRequest> oQuad::mouse_press(util::StateInfo updateinfo) {
                if (this->bound1.contains(updateinfo.position) || this->bound2.contains(updateinfo.position)) {
                    printf("Pressed\n");
                }
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
        }
    }
}