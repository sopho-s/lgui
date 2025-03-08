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
    lgui::drawables::objects::oTriangle triangle = lgui::drawables::objects::oTriangle(lgui::util::Point(100, 100), lgui::util::Point(0, 0), lgui::util::Point(200, 0), lgui::util::Point(200, 200), lgui::util::Colour(1, 0, 0, 1));
    window.add_object("tri1", &triangle);
    lgui::drawables::objects::animations::Move move = lgui::drawables::objects::animations::Move(100, 100, 14.1, 200, 200);
    triangle.give_animation(&move);
    lgui::drawables::objects::animations::Rotate rotate = lgui::drawables::objects::animations::Rotate(360, 36);
    triangle.give_animation(&rotate);
    window.main_loop(60);
    return 0;
}