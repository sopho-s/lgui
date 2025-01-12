#include <cmath>
#include "../../../util/util.h"
#pragma once

namespace lgui {
    namespace drawables {
        namespace objects {
            namespace animations {
                class Animation {
                public:
                    Animation() {}
                    virtual ~Animation() {}
                    virtual util::ObjectRequest update(float deltatime) = 0;
                };

                class Move : public Animation {
                private:
                    float x, y;
                    float speed;
                    float targetx, targety;
                public:
                    Move(float x, float y, float speed, float targetx, float targety) {
                        this->x = x;
                        this->y = y;
                        this->speed = speed;
                        this->targetx = targetx;
                        this->targety = targety;
                    }
                    util::ObjectRequest update(float deltatime) override {
                        float xdiff = this->targetx - this->x;
                        float ydiff = this->targety - this->y;
                        float distance = sqrt(xdiff * xdiff + ydiff * ydiff);
                        if (distance < this->speed * deltatime) {
                            this->x = this->targetx;
                            this->y = this->targety;
                        } else {
                            this->x += xdiff / distance * this->speed * deltatime;
                            this->y += ydiff / distance * this->speed * deltatime;
                        }
                        util::ObjectRequest request;
                        request.type = UPDATEPOSITION;
                        request.x = this->x;
                        request.y = this->y;
                        return request;
                    }
                };
            }
        }
    }
}