# lgui

lgui is an easy but basic gui library for c++

```c++
#include "window/window.h"
#include "util/util.h"
#include "drawables/objects/objects.h"
#include "drawables/objects/animations/animations.h"

int main() {
    lgui::window::lWindow window = lgui::window::lWindow();
    window.set_size(800, 600);
    window.set_background_colour(lgui::util::Colour(255, 255, 255, 0));
    window.set_title("I have a title");
    lgui::drawables::objects::oRectangle rect = lgui::drawables::objects::oRectangle(0, 0, 100, 100, lgui::util::Colour(255, 255, 0, 0));
    window.add_object("rect1", &rect);
    lgui::drawables::objects::animations::Move move = lgui::drawables::objects::animations::Move(0, 0, 100, 300, 200);
    rect.give_animation(&move);
    window.show();
    window.main_loop(60);
}
```
