#include "button.h"

void (*Button::buttonFunc)(void) = nullptr;

Button::Button(InputPin* k, PullType p)
{
    key = k;
    pull = p;
    scan();
}

bool Button::isPressed()
{
    bool old = pressed;
    scan();
    return !old && pressed;
}

bool Button::isReleased()
{
    bool old = pressed;
    scan();
    return old && !pressed;
}

bool Button::isUp()
{
    bool old = pressed;
    scan();
    return !old && !pressed;
}

bool Button::isDown()
{
     bool old = pressed;
    scan();
    return old && pressed;
}

void Button::init(void (*debouncer)(void))
{
    buttonFunc = debouncer;
}

void Button::scan()
{
    bool v = key->digitalRead();
    pressed = (v && pull) || (!v && !pull);
    if(buttonFunc != nullptr){
       (*buttonFunc)();
    }
}
