#include"../stm32f103/mcu.h"
#include"../drivers/pin.h"

#pragma once

enum I2CState{
    TX,
    RX
};

enum class I2cAddressFormat{
    SEVEN,
    TEN,
    DUAL
};

struct I2cConfig
{
    I2cAddressFormat addr_fmt;
    uint16_t own_addr;
    uint8_t freq_kHz;
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
    bool read(uint8_t slave_addr, uint8_t mem_addr, char* data);
    bool addressFound();
private:
    i2c_t* i;
    OutputPin scl;
    OutputPin sda;
    bool addr7_mode;
    bool is_master;
    bool addr_sent;
    void start();
    void stop();
    bool busBusy();
    bool send7BitAddress(uint16_t slave_addr, I2CState master_state);
    bool send10BitAddress(uint16_t slave_addr, I2CState master_state);
    bool clearAddressBit();
    bool toMaster(uint16_t slave_addr, I2CState master_state=I2CState::TX);
    void waitRxNotEmpty();
    void waitTxEmpty();
};