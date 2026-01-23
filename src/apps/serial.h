#pragma once
#include<type_traits>
#include"../stm32f103/mcu.h"
#include"../apps/pin.h"

#define ENABLE_TRANSMITTER  0x00000001
#define ENABLE_RECEIVER     0x00000002

enum Mode{
    TX_RX = ENABLE_TRANSMITTER | ENABLE_RECEIVER,
    TX_ONLY = ENABLE_TRANSMITTER,
    RX_ONLY = ENABLE_RECEIVER
};

enum BaudRate {
    BR9600 = 9600,
    BR19200 = 19200,
    BR38400 = 38400,
    BR57600 = 57600,
    BR115200 = 115200,
};

enum DataBits{
    EIGHT,
    NINE
};

enum Parity{
    EVEN,
    ODD
};

enum StopBit{
    ONE, 
    TWO
};

struct SerialConfig
{
    Mode mode;
    DataBits dataBits;
    Parity   parity;
    StopBit stopBit;
    bool isSynch;
};

struct Uart1{
    typedef PortA SerialPort; 
    static constexpr uint8_t tx_pin = 9;
    static constexpr uint8_t rx_pin = 10;
    static constexpr uint8_t clk_pin = 8;
};

struct Uart2{
    typedef PortA SerialPort; 
    static constexpr uint8_t tx_pin = 2;
    static constexpr uint8_t rx_pin = 3;
    static constexpr uint8_t clk_pin = 4;
};

struct Uart3{
    typedef PortB SerialPort; 
    static constexpr uint8_t tx_pin = 10;
    static constexpr uint8_t rx_pin = 11;
    static constexpr uint8_t clk_pin = 12;
};

struct Serial{
    template<class U = Uart1>
    Serial(U _, SerialConfig* config, const STM32f103c8* s);
    void write(char ch);
    void write(const char* str);
    char read();
    bool available();
    void begin(BaudRate br);
private:
    uart_t* u;
    OutputPin tx;
    InputPin rx;
    OutputPin clk;
    uint32_t freq;
    void configure(SerialConfig* config);
};

template <class U>
Serial::Serial(U _, SerialConfig *config, const STM32f103c8 *s)
{
    U::SerialPort::init(s);
    s->enable_peripheral(0, clock_sel_t::APB2);//Enable AF
    if(config->mode & ENABLE_TRANSMITTER){
        U::SerialPort::fastSpeedOutput(U::tx_pin, OutputType::AlternatePP, &tx);
    }
    if(config->mode & ENABLE_RECEIVER){
        U::SerialPort::input(U::rx_pin, InputType::Floating, &rx);
        //rx.pullUp();
    }
    if(config->isSynch){
        U::SerialPort::fastSpeedOutput(U::clk_pin, OutputType::AlternatePP, &clk);       
    }
    
    if constexpr (std::is_same_v<U, Uart1>){
        u = s->uart1;
        freq = clock_freq();
        s->enable_peripheral(14, clock_sel_t::APB2);
    }else if constexpr (std::is_same_v<U, Uart2>){
        u = s->uart2;
        freq = clock_apb1_freq();
        s->enable_peripheral(17, clock_sel_t::APB1);
    }else if constexpr (std::is_same_v<U, Uart3>){
        u = s->uart3;
        freq = clock_apb1_freq();
        s->enable_peripheral(18, clock_sel_t::APB1);
    }else{
        
    }
    configure(config);
}