#include "serial.h"

template <>
Serial::Serial(Uart1 _u, SerialType t, UartConfig* config, const STM32f103c8* s)
:type(t)
{
    u = s->uart1;
    s->enable_peripheral(14, clock_sel_t::APB2);
    PortA::init(s); 
    configure<PORT::A>(_u.mode, config, 9, 10, 8);
}

template <>
Serial::Serial(Uart2 _u,SerialType t, UartConfig* config, const STM32f103c8* s)
:type(t)
{
    u = s->uart2;
    s->enable_peripheral(17, clock_sel_t::APB1);
    PortA::init(s);
    configure<PORT::A>(_u.mode, config, 2, 3, 4);
}

template <>
Serial::Serial(Uart3 _u, SerialType t, UartConfig* config, const STM32f103c8* s)
:type(t)
{
    u = s->uart3;
    s->enable_peripheral(18, clock_sel_t::APB1);
    PortB::init(s);
    configure<PORT::B>(_u.mode, config, 10, 11, 12);
}

void Serial::write(uint8_t data)
{
    usart_write(u, data);
}

void Serial::write(uint8_t *data, uint8_t len)
{
    for(int i=0; i < len; ++i){
        usart_write(u, *(data + i));
    }
}

uint8_t Serial::read()
{
    return usart_read(u);
}

bool Serial::available()
{
    return usart_data_available(u);
}