#include"../stm32f103/mcu.h"
#include"../apps/pin.h"

#pragma once

enum SpiMode{
    MASTER,
    SLAVE
};

enum SpiClockEdge{
    RISING,
    FALLING
};

enum class SpiDataFrame{
    EIGHT,
    SIXTEEN
};

enum SpiDataFormat{
    LSB_FIRST,
    MSB_FIRST
};

enum SpiBaudRate{
    DIV_2   = 0,
    DIV_4   = 1,
    DIV_8   = 2,
    DIV_16  = 3,
    DIV_32  = 4,
    DIV_64  = 5,
    DIV_128 = 6,
    DIV_256 = 7
};

struct SpiConfig
{
    SpiMode mode;
    SpiClockEdge edge;
    SpiDataFormat format;
    SpiDataFrame  frame;
    SpiBaudRate br;
};

struct Spi1{
    typedef PortA SerialPort; 
    static constexpr uint8_t mosi_pin = 7;
    static constexpr uint8_t miso_pin = 6;
    static constexpr uint8_t clk_pin = 5;
    static constexpr uint8_t nss_pin = 4;
};

struct Spi2{
    typedef PortB SerialPort; 
    static constexpr uint8_t mosi_pin = 15;
    static constexpr uint8_t miso_pin = 14;
    static constexpr uint8_t clk_pin = 13;
    static constexpr uint8_t nss_pin = 12;
};

struct Spi3{
    typedef PortB SerialPort; 
    static constexpr uint8_t mosi_pin = 5;
    static constexpr uint8_t miso_pin = 4;
    static constexpr uint8_t clk_pin = 3;
};

struct SpiInterface{
    friend class Serial;
    void write(char ch);
    void write(const char* str);
    void write(char16_t ch);
    void write(const char16_t* str);
    char read();
    char16_t read(int);
    bool available();
private:
    spi_t* s;
};
