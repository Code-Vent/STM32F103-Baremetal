#include"../stm32f103/mcu.h"
#include"../apps/pin.h"

#pragma once

enum class I2cAddressFormat{
    SEVEN,
    TEN,
    DUAL
};

struct I2cConfig
{
    I2cAddressFormat addr_fmt;
    uint16_t addr;
    uint8_t freq_MHz;
};

struct I2c1{
    typedef PortB SerialPort; 
    static constexpr uint8_t scl_pin = 6;
    static constexpr uint8_t sda_pin = 7;
};

struct I2c2{
    typedef PortB SerialPort; 
    static constexpr uint8_t scl_pin = 10;
    static constexpr uint8_t sda_pin = 11;
};

struct I2cInterface{
    friend class Serial;
    void write(char ch);
    void write(const char* str);
    char read();
    bool available();
private:
    i2c_t* i;
    OutputPin scl;
    OutputPin sda;
};