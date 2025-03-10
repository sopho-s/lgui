#include "../../util/util.h"
#pragma once
namespace lgui {
    namespace drawables {
        namespace objects {
            /**
             * @brief A base class for all bounds
             * 
             */
            class Bound {
                public:
                    /**
                     * @brief Construct a new Bound object
                     * 
                     */
                    Bound() {}
                    /**
                     * @brief Destroy the Bound object
                     * 
                     */
                    virtual ~Bound() {}
                    /**
                     * @brief Checks if the bound contains a point
                     * 
                     * @param x The x position of the point
                     * @param y The y position of the point
                     * @return true If the bound contains the point
                     * @return false If the bound does not contain the point
                     */
                    virtual bool contains(util::Point point) = 0;
                    /**
                     * @brief Sets the position of the bound
                     * 
                     * @param x The x position of the bound
                     * @param y The y position of the bound
                     */
                    virtual void set_position(util::Point point) = 0;
                    /**
                     * @brief Sets the size of the bound
                     * 
                     * @param width The width of the bound
                     * @param height The height of the bound
                     */
                    virtual void set_size(int width, int height) = 0;
            };

            class TriangleBound : public Bound {
                private:
                    util::Point center;
                    util::Point p1, p2, p3;
                public:
                    TriangleBound() {}
                    TriangleBound(util::Point center, util::Point p1, util::Point p2, util::Point p3) {
                        this->center = center;
                        this->p1 = p1;
                        this->p2 = p2;
                        this->p3 = p3;
                    }
                    bool contains(util::Point point) override {
                        double theta1 = ((this->p2.ytrue - this->p3.ytrue) * (point.xtrue - this->p3.xtrue) + (this->p3.xtrue - this->p2.xtrue) * (point.ytrue - this->p3.ytrue)) / ((this->p2.ytrue - this->p3.ytrue) * (this->p1.xtrue - this->p3.xtrue) + (this->p3.xtrue - this->p2.xtrue) * (this->p1.ytrue - this->p3.ytrue));
                        double theta2 = ((this->p3.ytrue - this->p1.ytrue) * (point.xtrue - this->p3.xtrue) + (this->p1.xtrue - this->p3.xtrue) * (point.ytrue - this->p3.ytrue)) / ((this->p2.ytrue - this->p3.ytrue) * (this->p1.xtrue - this->p3.xtrue) + (this->p3.xtrue - this->p2.xtrue) * (this->p1.ytrue - this->p3.ytrue));
                        double theta3 = 1 - theta1 - theta2;
                        if (theta1 >= 0 && theta1 <= 1 && theta2 >= 0 && theta2 <= 1 && theta3 >= 0 && theta3 <= 1) {
                            return true;
                        }
                        return false;
                    }
                    void set_position(util::Point point) override {
                        util::Point diff = this->center - point;
                        this->center = point;
                        this->p1 = this->p1 - diff;
                        this->p2 = this->p2 - diff;
                        this->p3 = this->p3 - diff;
                    }

                    void set_points(util::Point p1, util::Point p2, util::Point p3) {
                        this->p1 = p1;
                        this->p2 = p2;
                        this->p3 = p3;
                    }
                    
                    void set_size(int width, int height) override {
                        ;
                    }
            };
        }
    }
}