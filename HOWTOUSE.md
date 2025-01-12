# Getting started

To get started lets make a basic window

```c++
#include "window/window.h"

int main() {
    lgui::window::lWindow window = lgui::window::lWindow();
    window.set_size(800, 600);
    window.show();
}
```

This will create a blank 800*600 window, but you will notice when you run this code it will not show a window, this is because as soon as the window is created the code finished and the window is destroyed

To fix this we will add a main loop to the window that will run until the program is shut or the window is closed

```c++
#include "window/window.h"

int main() {
    lgui::window::lWindow window = lgui::window::lWindow();
    window.set_size(800, 600);
    window.show();
    window.main_loop(60);
}
```

Now a window is displayed, but it's pretty dark, lets light it up

```c++
#include "window/window.h"
#include "util/util.h"

int main() {
    lgui::window::lWindow window = lgui::window::lWindow();
    window.set_size(800, 600);
    window.set_background_colour(lgui::util::Colour(255, 255, 255, 0));
    window.show();
    window.main_loop(60);
}
```

Now we have a white background, lets give it a title

```c++
#include "window/window.h"
#include "util/util.h"

int main() {
    lgui::window::lWindow window = lgui::window::lWindow();
    window.set_size(800, 600);
    window.set_background_colour(lgui::util::Colour(255, 255, 255, 0));
    window.set_title("I have a title");
    window.show();
    window.main_loop(60);
}
```

Now lets add an object to this blank screen

```c++
#include "window/window.h"
#include "util/util.h"
#include "drawables/objects/objects.h"

int main() {
    lgui::window::lWindow window = lgui::window::lWindow();
    window.set_size(800, 600);
    window.set_background_colour(lgui::util::Colour(255, 255, 255, 0));
    window.set_title("I have a title");
    lgui::drawables::objects::oRectangle rect = lgui::drawables::objects::oRectangle(0, 0, 100, 100, lgui::util::Colour(255, 255, 0, 0));
    window.add_object("rect1", &rect);
    window.show();
    window.main_loop(60);
}
```

Lets now make it move about a bit

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

Incase you've gotten a bit lost lets explain the code line by line

```c++
lgui::window::lWindow window = lgui::window::lWindow();
```

This line creates a simple window, thats it

```c++
window.set_size(800, 600);
```

This line sets the size of the window

```c++
window.set_background_colour(lgui::util::Colour(255, 255, 255, 0));
```

This line sets the background colour of the background

```c++
window.set_title("I have a title");
```

This line changes the title of the window

```c++
window.show();
```

This line shows the window

```c++
lgui::drawables::objects::oRectangle rect = lgui::drawables::objects::oRectangle(0, 0, 100, 100, lgui::util::Colour(255, 255, 0, 0));
```

This creates a basic rectangle object at 0, 0 with a size of 100, 100

```c++
window.add_object("rect1", &rect);
```

This adds the object with the name of the object so you can reference it later

```c++
lgui::drawables::objects::animations::Move move = lgui::drawables::objects::animations::Move(0, 0, 100, 300, 200);
```

This makes an animation that moves the object from 0, 0 to 300, 200 at a speed of 100 pixels a second

```c++
rect.give_animation(&move);
```

This gives the animation to the rectangle for it to play

```c++
window.main_loop(60);
```

This initiates the game loop at 60 updates a second

And thats it, for getting started, now lets go into a little more advanced stuff

# Defining your own Objects and Drawables

Lets start by explaining the difference between Objects and Drawables

Here's the simple explination, Objects are persistent, Drawables are non-persistent

Here's a more complex explination, Drawables are used to tell the window what to draw on the screen. Once the window is told what to draw, on any future updates the Drawable will be cleared from the screen. Objects contain drawables, but are given to the window, every update each object is told to update, in which it will use its Drawable to display to the screen. This means when a Object is added to the window it will stay on the window until removed by the user

Now lets get onto how to define your own Objects and Drawables

Lets start with Drawables

## Defining Drawables

When redefining your own Drawable, you will most likely be using the base lDrawable object

Drawables have one function which is Draw

Here is the definition on the base object

```c++
/**
 * @brief Draws the object on the window
 * 
 * @param display The display to draw on
 * @param window The window to draw on
 * @param gc The graphics context to draw with
 */
virtual void draw(Display* display, Window& window, GC& gc) = 0;
```

And here is the basic lRectangle Drawable with its own code for the draw function

```c++
void lRectangle::draw(Display* display, Window& window, GC& gc) {
    XColor draw_colour;
    Colormap colourmap = DefaultColormap(display, DefaultScreen(display));
    draw_colour.red = this->colour.r;
    draw_colour.green = this->colour.g;
    draw_colour.blue = this->colour.b;
    draw_colour.flags = DoRed | DoGreen | DoBlue;
    if (!XAllocColor(display, colourmap, &draw_colour)) {
        return;
    }
    XSetForeground(display, gc, draw_colour.pixel);
    XSetLineAttributes(display, gc, 1, LineSolid, CapButt, JoinBevel);
    XSetFillStyle(display, gc, FillSolid);
    if (this->filled) {
        XFillRectangle(display, window, gc, x, y, (unsigned int)width, (unsigned int)height);
    } else {
        XDrawRectangle(display, window, gc, x, y, (unsigned int)width, (unsigned int)height);
    }
}
```

Lets break this down

```c++
XColor draw_colour;
Colormap colourmap = DefaultColormap(display, DefaultScreen(display));
draw_colour.red = this->colour.r;
draw_colour.green = this->colour.g;
draw_colour.blue = this->colour.b;
draw_colour.flags = DoRed | DoGreen | DoBlue;
if (!XAllocColor(display, colourmap, &draw_colour)) {
    return;
}
XSetForeground(display, gc, draw_colour.pixel);
```

First you create two objects: `XColor` and `Colormap`. `XColor` is what is used to colour the rectangle, `Colormap` is used to find the appropriate colour for the `XColor`

You then set the RGB values of `XColor` and tell `XColor` to use all the colours

Then you allocate the colour using the `Colormap` so the colour is correctly displayed on the screen

Lastly you change the foreground colour so that the rectangle will be displayed in the correct colour

```c++
XSetLineAttributes(display, gc, 1, LineSolid, CapButt, JoinBevel);
XSetFillStyle(display, gc, FillSolid);
if (this->filled) {
    XFillRectangle(display, window, gc, x, y, width, height);
} else {
    XDrawRectangle(display, window, gc, x, y, width, height);
}
```

You then start by setting the line attributes of the rectangle, currently it has a 1 pixel thick line along with the rest of the settings

Then you set the fill style for the rectangle

Lastly depending on whether it's filled or not you then draw the rectangle or fill the rectangle

This is the general gyst of what you need to do to make your own Drawable, just redefine this draw function

## Defining Objects

When redefining your own Object, you will most likely be using the base Object object

Objects have multiple important functions, here are the notable ones

```c++
virtual void draw(Display* display, Window& window, GC& gc) = 0;
virtual void give_animation(animations::Animation* animation) = 0;
virtual std::vector<util::WindowRequest> update(float deltatime) = 0;
virtual std::vector<util::WindowRequest> mouse_move(util::StateInfo updateinfo) = 0;
virtual std::vector<util::WindowRequest> mouse_press(util::StateInfo updateinfo) = 0;
virtual std::vector<util::WindowRequest> mouse_release(util::StateInfo updateinfo) = 0;
virtual std::vector<util::WindowRequest> key_press(util::StateInfo updateinfo) = 0;
virtual std::vector<util::WindowRequest> key_release(util::StateInfo updateinfo) = 0;
```

Lets go through them

### draw

The draw function can simply call the drawable's draw function

```c++
void oRectangle::draw(Display* display, Window& window, GC& gc) {
    this->rect->draw(display, window, gc);
}
```

### give_animation

This gives an animation to the object to run

```c++
void give_animation(animations::Animation* animation) override {
    this->animations.push_back(animation);
}
```

### update

This is called by the window every update tick

```c++
std::vector<util::WindowRequest> oRectangle::update(float deltatime) {
    for (animations::Animation* animation : this->animations) {
        util::ObjectRequest request = animation->update(deltatime);
        if (request.type & UPDATEPOSITION) {
            this->rect->x = request.x;
            this->rect->y = request.y;
            this->bound.set_position(request.x, request.y);
        }
    }
    return std::vector<util::WindowRequest>();
}
```

### other event functions

The remaining functions are called upon their specific event occuring

### Explaining specific objects used

The first notable object is `WindowRequest`, it is used to ask the window to change something about itself, such as size, position, colour, etc

It has the following types:

- UPDATESIZE - Will update the size of the window
- UPDATEPOSITION - Will update the position of the window
- UPDATETITLE - Will update the title of the window
- UPDATEBACKGROUNDCOLOUR - Will update the background colour
- UPDATEBORDERCOLOUR - Will update the border colour
- UPDATEBORDERWIDTH - Will update the border width
- UPDATEBORDERRADIUS - Will update the border radius
- NOTYPE - All updates will be applied except CLOSE
- CLOSE - Will close the window

It is notable that these are masks, so you can apply multiple masks instead of making multiple requests

The other notable object is `ObjectRequest`, it is used by animations to request that an object change something about itself

It has the following types:

- NOCHANGE - Does nothing
- UPDATESIZE - Will update the size
- UPDATEPOSITION - Will update the position
- UPDATEROTATION - Will update the rotation
- UPDATECOLOUR - Will update the colour
- ALLCHANGES - Will update everything

# Defining Animations

Animations are used to encapsulate certain actions into an object. The base animation has a simple update function

```c++
virtual util::ObjectRequest update(float deltatime) = 0;
```

This should be called every update tick, and will pass data back to the object about what it should do on this tick