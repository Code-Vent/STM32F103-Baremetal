#pragma once
#include<type_traits>
#include"uart_defs.h"
#include"spi_defs.h"
#include"i2c_defs.h"

inline uint32_t calculate_brr_value(uint32_t freq, uint32_t baud){
    return (freq +(baud/2)) / baud;
}

void configure_uart(uart_t* u, UartConfig* config);
void configure_spi(spi_t* s, SpiConfig* config);
void configure_i2c(i2c_t* i, I2cConfig* config);

struct Serial{
    template<class U = Uart1>
    Serial(U _, UartConfig* config, UartInterface*, const STM32f103c8* s);
    template<class S = Spi1>
    Serial(S _, SpiConfig* config, SpiInterface*, const STM32f103c8* s);
    template<class I = I2c1>
    Serial(I _, I2cConfig* config, I2cInterface*, const STM32f103c8* s);
};

template <class U>
Serial::Serial(U _, UartConfig *config, UartInterface* ui, const STM32f103c8 *s)
{
    OutputPin out;
    InputPin in;
    U::SerialPort::init(s);
    s->enable_peripheral(0, clock_sel_t::APB2);//Enable AF
    if(config->mode & ENABLE_TRANSMITTER){
        U::SerialPort::fastSpeedOutput(U::tx_pin, OutputType::AlternatePP, &out);
    }
    if(config->mode & ENABLE_RECEIVER){
        U::SerialPort::input(U::rx_pin, InputType::Floating, &in);
    }
    if(config->enableClock){
        U::SerialPort::fastSpeedOutput(U::clk_pin, OutputType::AlternatePP, &out);       
    }
    
    if constexpr (std::is_same_v<U, Uart1>){
        s->enable_peripheral(14, clock_sel_t::APB2);
        ui->u = s->uart1;
    }else if constexpr (std::is_same_v<U, Uart2>){
        s->enable_peripheral(17, clock_sel_t::APB1);
        ui->u = s->uart2;
    }else if constexpr (std::is_same_v<U, Uart3>){
        s->enable_peripheral(18, clock_sel_t::APB1);
        ui->u = s->uart3;
    }else{
        static_assert(false);
    }
    configure_uart(ui->u, config);
}

template <class S>
Serial::Serial(S _, SpiConfig *config, SpiInterface* si, const STM32f103c8 *s)
{
    OutputPin out;
    InputPin in;
    S::SerialPort::init(s);
    s->enable_peripheral(0, clock_sel_t::APB2);//Enable AF
    if(config->mode == SpiMode::MASTER){
        S::SerialPort::fastSpeedOutput(S::mosi_pin, OutputType::AlternatePP, &out);
        S::SerialPort::input(S::miso_pin, InputType::Floating, &in);
        S::SerialPort::fastSpeedOutput(S::clk_pin, OutputType::AlternatePP, &out);
    }else{
        S::SerialPort::input(S::mosi_pin, InputType::Floating, &in);
        S::SerialPort::fastSpeedOutput(S::miso_pin, OutputType::AlternatePP, &out);       
        S::SerialPort::input(S::clk_pin, InputType::Floating, &in);
    }

    if constexpr (std::is_same_v<S, Spi1>){
        s->enable_peripheral(12, clock_sel_t::APB2);        
        si->s = s->spi1;
    }else if constexpr (std::is_same_v<S, Spi2>){
        s->enable_peripheral(14, clock_sel_t::APB1);
        si->s = s->spi2;
    }else if constexpr (std::is_same_v<S, Spi3>){
        s->enable_peripheral(15, clock_sel_t::APB1);
        si->s = s->spi3;
    }else{
        static_assert(false);
    }
    configure_spi(si->s, config);
}

template <class I>
Serial::Serial(I _, I2cConfig* config, I2cInterface* ii, const STM32f103c8 *s)
{
    I::SerialPort::init(s);
    s->enable_peripheral(0, clock_sel_t::APB2);//Enable AF
    I::SerialPort::fastSpeedOutput(I::scl_pin, OutputType::AlternateOD, &ii->scl);
    I::SerialPort::fastSpeedOutput(I::sda_pin, OutputType::AlternateOD, &ii->sda);

    if constexpr (std::is_same_v<I, I2c1>){
        s->enable_peripheral(21, clock_sel_t::APB1);        
        ii->i = s->i2c1;
    }else if constexpr (std::is_same_v<I, I2c2>){
        s->enable_peripheral(22, clock_sel_t::APB1);
        ii->i = s->i2c2;
    }else{
        static_assert(false);
    }
}
