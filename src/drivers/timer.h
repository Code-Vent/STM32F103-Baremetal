#pragma once

#include"../registers/tim.h"
#include"timer_defs.h"

class Timer
{
public:
    Timer(Tim_x t);
    void start();
    void block();
    operator bool();
private:
};