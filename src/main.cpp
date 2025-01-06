#include "window/window.h"
#include <unistd.h>
int main() {
    lgui::window::lWindow window = lgui::window::lWindow();
    window.set_size(800, 600);
    window.set_background_colour(lgui::util::Colour((unsigned short)0xFFFF, (unsigned short)0, (unsigned short)0, (unsigned short)0));
    window.show();
    sleep(10);
    window.set_background_colour(lgui::util::Colour((unsigned short)0, (unsigned short)0xFFFF, (unsigned short)0, (unsigned short)0));
    window.flush();
    sleep(10);
    return 0;
}