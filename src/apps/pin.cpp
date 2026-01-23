#include"pin.h"

template<>
void Port<PORT::A>::init(const STM32f103c8* s) {
    s->enable_peripheral(2, clock_sel_t::APB2);
    gpio_ = s->gpioa;
    return;
}

template<>
void Port<PORT::B>::init(const STM32f103c8* s) {
    s->enable_peripheral(3, clock_sel_t::APB2);
    gpio_ = s->gpiob;
    return;
}

template<>
void Port<PORT::C>::init(const STM32f103c8* s) {
    s->enable_peripheral(4, clock_sel_t::APB2);
    gpio_ = s->gpioc;
    return;
}

void OutputPin::digitalWrite(bool l){
    gpio_write(port, num, l);
}

void OutputPin::analogWrite(uint8_t value) {

}

bool InputPin::digitalRead()
{
    return gpio_read(port, num);
}

uint8_t InputPin::analogRead()
{
    return 0;
}

void InputPin::pullUp()
{
    gpio_write(port, num, true);
}

void InputPin::pullDown()
{
    gpio_write(port, num, false);
}

void configure(gpio_t *g, uint8_t pin_num, uint32_t bits)
{
    uint32_t clear_mask = 0, set_mask = 0;
    if(pin_num < 8){
        clear_mask = ~(15u << (4 * pin_num));
        gpio_crl_clear(g, clear_mask);
        set_mask = bits << (4 * pin_num);
        gpio_crl_set(g, set_mask);
    }else{
        pin_num -= 8;
        clear_mask = ~(15u << (4 * pin_num));
        gpio_crh_clear(g, clear_mask);
        set_mask = bits << (4 * pin_num);
        gpio_crh_set(g, set_mask);
    }
}
