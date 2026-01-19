#pragma once
#include"../stm32f103/mcu.h"
#include"../apps/pin.h"

#define ENABLE_TRANSMITTER  0x00000001
#define ENABLE_RECEIVER     0x00000002

enum Mode{
    TX_RX = ENABLE_TRANSMITTER | ENABLE_RECEIVER,
    TX_ONLY = ENABLE_TRANSMITTER,
    RX_ONLY = ENABLE_RECEIVER
};

struct Uart1{Mode mode = TX_RX;};
struct Uart2{Mode mode = TX_RX;};
struct Uart3{Mode mode = TX_RX;};

enum SerialType{Synch, Asynch};

struct Serial{
    template<class U>
    Serial(U _u, SerialType st, UartConfig* config, const STM32f103c8* s);
    void write(uint8_t data);
    void write(uint8_t* data, uint8_t len);
    uint8_t read();
    bool available();
    const SerialType type;
private:
    uart_t* u;
    OutputPin tx;
    InputPin rx;
    OutputPin clk;
    template<PORT T, class U = Port<T>>
    void configure(Mode mode, UartConfig* config, uint8_t tx_pin, uint8_t rx_pin, uint8_t clk_pin);
};

template <PORT T, class U>
inline void Serial::configure(Mode mode, UartConfig *config, uint8_t tx_pin, uint8_t rx_pin, uint8_t clk_pin)
{
    if(type == SerialType::Asynch){
        basic_uart_config(u, config);
    }else{ 
        basic_usart_config(u, config);
        U::mediumSpeedOutput(clk_pin, OutputType::AlternatePP, &clk);       
    }
    if(mode & ENABLE_TRANSMITTER){
        U::mediumSpeedOutput(tx_pin, OutputType::AlternatePP, &tx);
        usart_enable_tx(u);
    }
    if(mode & ENABLE_RECEIVER){
        U::input(rx_pin, InputType::Pulled, &rx);
        rx.pullUp();
        usart_enable_rx(u);
    }
}
