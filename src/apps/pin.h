#pragma once

#include"../stm32f103/mcu.h"

enum OutputType{
    PushPull = 0,
    OpenDrain = 1,
    AlternatePP = 2,
    AlternateOD = 3,
};

enum InputType{
    Analog = 0,
    Floating = 1,
    Pulled = 2,
};

struct OutputPin{
    void digitalWrite(bool level);
    void analogWrite(uint8_t value);
    OutputPin() = default;
    gpio_t* port;
    uint8_t num;
};

struct InputPin{
    bool digitalRead();
    uint8_t analogRead();
    void pullUp();
    void pullDown();
    InputPin() = default;
    gpio_t* port;
    uint8_t num;
};

void configure(gpio_t* g, uint8_t pin_num, uint32_t bits);

enum PORT{
    A, B, C
};

template<PORT T>
class Port{
public:
    static void init(const STM32f103c8*);
    static void fastSpeedOutput(uint8_t pin_num, OutputType, OutputPin* pin);
    static void mediumSpeedOutput(uint8_t pin_num, OutputType, OutputPin* pin);
    static void slowSpeedOutput(uint8_t pin_num, OutputType, OutputPin* pin);

    static void input(uint8_t pin_num, InputType, InputPin* pin);
private:
    static gpio_t* gpio_;
};

template<PORT T>
gpio_t* Port<T>::gpio_ = nullptr;

template<PORT T>
void Port<T>::fastSpeedOutput(uint8_t pin_num, OutputType t, OutputPin* pin){
    //gpio_init(gpio_, pin_num, t | CONFIG_PIN_AS_FAST_SPEED_OUTPUT);
    uint32_t config_bits = (uint32_t(t) << 2) | 3u;
    configure(gpio_, pin_num, config_bits);
    pin->port = gpio_;
    pin->num = pin_num;
}

template<PORT T>
void Port<T>::mediumSpeedOutput(uint8_t pin_num, OutputType t, OutputPin* pin){
    //gpio_init(gpio_, pin_num, t | CONFIG_PIN_AS_MEDIUM_SPEED_OUTPUT);
    uint32_t config_bits = (uint32_t(t) << 2) | 1u;
    configure(gpio_, pin_num, config_bits);
    pin->port = gpio_;
    pin->num = pin_num;
}

template<PORT T>
void Port<T>::slowSpeedOutput(uint8_t pin_num, OutputType t, OutputPin* pin){
    //gpio_init(gpio_, pin_num, t | CONFIG_PIN_AS_LOW_SPEED_OUTPUT);
    uint32_t config_bits = (uint32_t(t) << 2) | 2u;
    configure(gpio_, pin_num, config_bits);
    pin->port = gpio_;
    pin->num = pin_num;
}

template <PORT T>
void Port<T>::input(uint8_t pin_num, InputType t, InputPin *pin)
{
    //gpio_init(gpio_, pin_num, type);
    uint32_t config_bits = (uint32_t(t) << 2);
    configure(gpio_, pin_num, config_bits);
    pin->port = gpio_;
    pin->num = pin_num;
}

using PortA = Port<PORT::A>;
using PortB = Port<PORT::B>;
using PortC = Port<PORT::C>;