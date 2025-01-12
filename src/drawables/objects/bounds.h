namespace lgui {
    namespace drawables {
        namespace objects {
            class Bound {
                public:
                    Bound() {}
                    virtual ~Bound() {}
                    virtual bool contains(int x, int y) = 0;
                    virtual void set_position(int x, int y) = 0;
                    virtual void set_size(int width, int height) = 0;
            };

            class RectangleBound : public Bound {
                private:
                    int x, y, width, height;
                public:
                    RectangleBound() {}
                    RectangleBound(int x, int y, int width, int height) {
                        this->x = x;
                        this->y = y;
                        this->width = width;
                        this->height = height;
                    }
                    bool contains(int x, int y) override {
                        return x >= this->x && x <= this->x + this->width && y >= this->y && y <= this->y + this->height;
                    }
                    void set_position(int x, int y) override {
                        this->x = x;
                        this->y = y;
                    }
                    void set_size(int width, int height) override {
                        this->width = width;
                        this->height = height;
                    }
            };

            class CircleBound : public Bound {
                private:
                    int x, y, radius;
                public:
                    CircleBound() {}
                    CircleBound(int x, int y, int radius) {
                        this->x = x;
                        this->y = y;
                        this->radius = radius;
                    }
                    bool contains(int x, int y) override {
                        return (x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) <= this->radius * this->radius;
                    }
                    void set_position(int x, int y) override {
                        this->x = x;
                        this->y = y;
                    }
                    void set_size(int width, int height) override {
                        this->radius = width;
                    }
            };
        }
    }
}