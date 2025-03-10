#include "window/window.h"
#include "drawables/drawables.h"
#include "drawables/objects/objects.h"
#include "drawables/objects/animations/animations.h"
#include "util/util.h"
#include <unistd.h>
#include <math.h>

int main() {
    lgui::window::lWindow window = lgui::window::lWindow();
    window.set_size(800, 600);
    window.set_background_colour(lgui::util::Colour(0, 0, 0, 0));
    window.set_title("I have a title");
    window.show();
    lgui::drawables::objects::oQuad quad = lgui::drawables::objects::oQuad(lgui::util::Point(50, 50), lgui::util::Point(0, 0), lgui::util::Point(100, 0), lgui::util::Point(100, 100), lgui::util::Point(0, 100), lgui::util::Colour(1, 0, 0, 1));
    window.add_object("quad1", &quad);
    lgui::drawables::objects::animations::Move move = lgui::drawables::objects::animations::Move(50, 50, 14.1, 150, 150);
    quad.give_animation(&move);
    lgui::drawables::objects::animations::Rotate rotate = lgui::drawables::objects::animations::Rotate(360, 36);
    quad.give_animation(&rotate);
    window.main_loop(60);
    return 0;
}