#include <cmath>
#include "../../../util/util.h"
#pragma once

namespace lgui {
    namespace drawables {
        namespace objects {
            namespace animations {
                /**
                 * @brief An animation class that is used to animate objects
                 * 
                 */
                class Animation {
                public:
                    /**
                     * @brief Construct a new Animation object
                     * 
                     */
                    Animation() {}
                    /**
                     * @brief Destroy the Animation object
                     * 
                     */
                    virtual ~Animation() {}
                    /**
                     * @brief Updates the animation
                     * 
                     * @param deltatime The time since the last update
                     * @return util::ObjectRequest The request to make to the object
                     */
                    virtual util::ObjectRequest update(float deltatime) = 0;
                };

                /**
                 * @brief A move animation that moves an object from one point to another
                 * 
                 */
                class Move : public Animation {
                private:
                    float x, y;
                    float speed;
                    float targetx, targety;
                public:
                    /**
                     * @brief Construct a new Move object
                     * 
                     * @param x The x position of the object
                     * @param y The y position of the object
                     * @param speed The speed of the object
                     * @param targetx The x position of the target
                     * @param targety The y position of the target
                     */
                    Move(float x, float y, float speed, float targetx, float targety) {
                        this->x = x;
                        this->y = y;
                        this->speed = speed;
                        this->targetx = targetx;
                        this->targety = targety;
                    }
                    /**
                     * @brief Updates the animation
                     * 
                     * @param deltatime The time since the last update
                     * @return util::ObjectRequest The request to make to the object
                     */
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
                        request.position = util::Point(this->x, this->y);
                        return request;
                    }
                };

                class Rotate : public Animation {
                    private:
                        float angle;
                        float speed;
                    public:
                        Rotate(float angle, float speed) {
                            this->angle = angle;
                            this->speed = speed;
                        }
                        /**
                         * @brief Updates the animation
                         * 
                         * @param deltatime The time since the last update
                         * @return util::ObjectRequest The request to make to the object
                         */
                        util::ObjectRequest update(float deltatime) override {
                            util::ObjectRequest request;
                            request.type = UPDATEROTATION;
                            request.rotation = this->speed * deltatime / 180 * M_PI * abs(this->angle) / this->angle;
                            if (abs(angle) <= 0.000001) {
                                angle = 0;
                                request.rotation = 0;
                            } else if (abs(angle) / 180 * M_PI < request.rotation) {
                                request.rotation = angle / 180 * M_PI;
                            }
                            angle -= request.rotation * 180 / M_PI;
                            return request;
                        }
                };
            }
        }
    }
}