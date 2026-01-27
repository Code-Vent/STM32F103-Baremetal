#include"../stm32f103/mcu.h"
#include"../apps/pin.h"

#pragma once

#define ENABLE_TRANSMITTER  0x00000001
#define ENABLE_RECEIVER     0x00000002

enum UartMode{
    TX_RX = ENABLE_TRANSMITTER | ENABLE_RECEIVER,
    TX_ONLY = ENABLE_TRANSMITTER,
    RX_ONLY = ENABLE_RECEIVER
};

enum UartBaudRate {
    BR9600 = 9600,
    BR19200 = 19200,
    BR38400 = 38400,
    BR57600 = 57600,
    BR115200 = 115200,
};

enum UartDataBits{
    EIGHT,
    NINE
};

enum UartParity{
    EVEN,
    ODD
};

enum UartStopBit{
    ONE, 
    TWO
};

struct UartConfig
{
    UartMode     mode;
    UartDataBits dataBits;
    UartParity   parity;
    UartStopBit  stopBit;
    UartBaudRate br;
    bool     enableClock;
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

struct UartInterface{
    friend class Serial;
    void write(char ch);
    void write(const char* str);
    char read();
    bool available();
private:
    uart_t* u;
};