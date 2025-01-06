#pragma once
namespace lgui {
    namespace util {
        struct Colour {
            unsigned short r, g, b, a;
            Colour() {
                this->r = 0;
                this->g = 0;
                this->b = 0;
                this->a = 0;
            }
            Colour(int r, int g, int b, int a) {
                this->r = r;
                this->g = g;
                this->b = b;
                this->a = a;
            }
        };
    }
}