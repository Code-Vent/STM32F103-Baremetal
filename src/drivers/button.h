#pragma once
#include"pin.h"

enum PullType{
    UP, DOWN
};

class Button{
public:
    Button(InputPin*, PullType);
    bool isPressed();
    bool isReleased();
    bool isUp();
    bool isDown();
    static void init(void (*debouncer)(void));
private:
    void scan();
    InputPin* key;
    bool pressed;
    PullType pull;
    static void (*buttonFunc) (void);
};