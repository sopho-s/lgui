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
                    virtual bool contains(int x, int y) = 0;
                    /**
                     * @brief Sets the position of the bound
                     * 
                     * @param x The x position of the bound
                     * @param y The y position of the bound
                     */
                    virtual void set_position(int x, int y) = 0;
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
                    util::Point p1, p2, p3;
                public:
                    TriangleBound() {}
                    TriangleBound(util::Point p1, util::Point p2, util::Point p3) {
                        this->p1 = p1;
                        this->p2 = p2;
                        this->p3 = p3;
                    }
                    bool contains(int x, int y) override {
                        return false;
                    }
                    void set_position(int x, int y) override {
                        this->p1.x += x;
                        this->p1.y += y;
                        this->p2.x += x;
                        this->p2.y += y;
                        this->p3.x += x;
                        this->p3.y += y;
                    }
                    void set_size(int width, int height) override {
                        ;
                    }
            };

            /**
             * @brief A rectangle bound
             * 
             */
            class RectangleBound : public Bound {
                private:
                    int x, y, width, height;
                public:
                    /**
                     * @brief Construct a new Rectangle Bound object
                     * 
                     */
                    RectangleBound() {}
                    /**
                     * @brief Construct a new Rectangle Bound object
                     * 
                     * @param x The x position of the bound
                     * @param y The y position of the bound
                     * @param width The width of the bound
                     * @param height The height of the bound
                     */
                    RectangleBound(int x, int y, int width, int height) {
                        this->x = x;
                        this->y = y;
                        this->width = width;
                        this->height = height;
                    }
                    /**
                     * @brief Checks if the bound contains a point
                     * 
                     * @param x The x position of the point
                     * @param y The y position of the point
                     * @return true If the bound contains the point
                     * @return false If the bound does not contain the point
                     */
                    bool contains(int x, int y) override {
                        return x >= this->x && x <= this->x + this->width && y >= this->y && y <= this->y + this->height;
                    }
                    /**
                     * @brief Sets the position of the bound
                     * 
                     * @param x The x position of the bound
                     * @param y The y position of the bound
                     */
                    void set_position(int x, int y) override {
                        this->x = x;
                        this->y = y;
                    }
                    /**
                     * @brief Sets the size of the bound
                     * 
                     * @param width The width of the bound
                     * @param height The height of the bound
                     */
                    void set_size(int width, int height) override {
                        this->width = width;
                        this->height = height;
                    }
            };

            /**
             * @brief A circle bound
             * 
             */
            class CircleBound : public Bound {
                private:
                    int x, y, radius;
                public:
                    /**
                     * @brief Construct a new Circle Bound object
                     * 
                     */
                    CircleBound() {}
                    /**
                     * @brief Construct a new Circle Bound object
                     * 
                     * @param x The x position of the bound
                     * @param y The y position of the bound
                     * @param radius The radius of the bound
                     */
                    CircleBound(int x, int y, int radius) {
                        this->x = x;
                        this->y = y;
                        this->radius = radius;
                    }
                    /**
                     * @brief Checks if the bound contains a point
                     * 
                     * @param x The x position of the point
                     * @param y The y position of the point
                     * @return true If the bound contains the point
                     * @return false If the bound does not contain the point
                     */
                    bool contains(int x, int y) override {
                        return (x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) <= this->radius * this->radius;
                    }
                    /**
                     * @brief Sets the position of the bound
                     * 
                     * @param x The x position of the bound
                     * @param y The y position of the bound
                     */
                    void set_position(int x, int y) override {
                        this->x = x;
                        this->y = y;
                    }
                    /**
                     * @brief Sets the size of the bound
                     * 
                     * @param width The width of the bound
                     * @param height The height of the bound
                     */
                    void set_size(int width, int height) override {
                        this->radius = width;
                    }
            };
        }
    }
}