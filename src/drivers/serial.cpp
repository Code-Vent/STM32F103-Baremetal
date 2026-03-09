#include "serial.h"
#include "spi_defs.h"
#include "i2c_defs.h"

void UartInterface::write(char ch)
{
    while(!usart_sr_read(u, SET_MASK(7)));//Wait for Transmitter Empty flag
    usart_write(u, ch);
}

void UartInterface::write(const char *str)
{
    while(*str){
        write(*str++);
    }
    while(!usart_sr_read(u, SET_MASK(6)));//Wait for Transmission Complete flag
    usart_sr_clear(u, CLEAR_MASK(6)); //Clear TC
}

char UartInterface::read()
{
    return usart_read(u);
}

bool UartInterface::available()
{
    return usart_sr_read(u, SET_MASK(5));//Read RXNE
}

void SpiInterface::write(char ch)
{
    while(!spi_sr_read(s, SET_MASK(1)));//Wait for Transmitter Empty flag
    spi_write(s, ch);
}

void SpiInterface::write(const char *str)
{
    while(*str){
        write(*str++);
    }
}

void SpiInterface::write(char16_t ch)
{
    while(!spi_sr_read(s, SET_MASK(1)));//Wait for Transmitter Empty flag
    spi_write(s, ch);
}

void SpiInterface::write(const char16_t *str)
{
    while(*str){
        write(*str++);
    }
}

char SpiInterface::read()
{
    return static_cast<char>(spi_read(s));
}

char16_t SpiInterface::read(int)
{
    return spi_read(s);
}

bool SpiInterface::available()
{
    return spi_sr_read(s, SET_MASK(0));//Read RXNE
}

void I2cInterface::write(char ch)
{
    i2c_write(i, ch);
    while(!i2c_sr1_read(i, SET_MASK(7)));//Wait for Transmitter Empty flag
    while(!i2c_sr1_read(i, SET_MASK(2)));//Wait for Byte transfer finished flag
}

void I2cInterface::write(const char *str)
{
    while(*str){
        i2c_write(i, *str++);
        while(!i2c_sr1_read(i, SET_MASK(7)));//Wait for Transmitter Empty flag
        while(!i2c_sr1_read(i, SET_MASK(2)));//Wait for Byte transfer finished flag
    }
}

bool I2cInterface::read(uint8_t slave_addr, uint8_t mem_addr, char* data)
{
    if(busBusy())
    {
        return false;
    }
    //Set ACK bit
    i2c_cr1_set(i, SET_MASK(10));//ACK
    if(toMaster(slave_addr, I2CState::TX)){
        i2c_write(i, mem_addr);
        waitTxEmpty();
        if(toMaster(slave_addr, I2CState::RX)){
            //Clear ACK bit
            i2c_cr1_clear(i, CLEAR_MASK(10));//ACK
            waitRxNotEmpty();
            *data = i2c_read(i);
            stop();
            return true;
        }else{
            //Error
            stop();
        }
    }else{
        //Error
        stop();
    }
    return false;
}

bool I2cInterface::addressFound()
{
    return i2c_sr1_read(i, SET_MASK(1));//Address Sent bit
}

void I2cInterface::waitRxNotEmpty()
{
    while(!i2c_sr1_read(i, SET_MASK(6)));//Read RXNE
}

void I2cInterface::waitTxEmpty()
{
    while(!i2c_sr1_read(i, SET_MASK(7)));//TXE;
}

bool I2cInterface::toMaster(uint16_t addr, I2CState st)
{
    start();
    if(addr7_mode){
        addr_sent = send7BitAddress(addr, st);
    }else{
        addr_sent = send10BitAddress(addr, st);
    }
    if(addr_sent){
        clearAddressBit();
    }
    return is_master && addr_sent;
}

void I2cInterface::start()
{
    addr_sent = false;
    i2c_cr1_set(i, SET_MASK(8));//START
    while(!i2c_sr1_read(i, SET_MASK(0)));
    is_master = i2c_sr2_read(i, SET_MASK(0));  
}

void I2cInterface::stop()
{
    addr_sent = false;
    //Generate stop condition
    i2c_cr1_set(i, SET_MASK(9));//Stop
    STM32f103c8::get()->delay_ms(30);
    is_master = i2c_sr2_read(i, SET_MASK(0));  
}

bool I2cInterface::busBusy()
{
    return i2c_sr2_read(i, SET_MASK(1));
}

bool I2cInterface::send10BitAddress(uint16_t slave_addr, I2CState master_state)
{
    //send  header (11110xx0)
    //slave address with LSB reset
    if(master_state == I2CState::RX){
        //send a repeated Start condition 
        //followed by the header (11110xx1)
    }
    return false;
}

bool I2cInterface::clearAddressBit()
{
    return i2c_sr1_read(i, 0) && i2c_sr2_read(i, 0);
}

bool I2cInterface::send7BitAddress(uint16_t slave_addr, I2CState master_state)
{
    i2c_write(i, uint8_t((slave_addr << 1) | (0x01 & master_state)));
    STM32f103c8::get()->delay_ms(1000);
    return i2c_sr1_read(i, SET_MASK(1));//Address Sent bit
}

void configure_uart(uart_t *u, UartConfig *config)
{
    usart_cr1_clear(u, CLEAR_MASK(13));//Disable UE
    if(config->dataBits == UartDataBits::EIGHT){
        usart_cr1_clear(u, CLEAR_MASK(12));
    }else{
        usart_cr1_set(u, SET_MASK(12));
    }
    usart_cr1_clear(u, CLEAR_MASK(10));//Disable Parity
    //if(config->parity == Parity::EVEN){
    //    usart_cr1_clear(u, CLEAR_MASK(9));
    //}else{
    //    usart_cr1_set(u, SET_MASK(9));
    //}

    if(config->stopBit == UartStopBit::ONE){
        usart_cr2_clear(u, CLEAR_MASK(13) & CLEAR_MASK(12));
    }else{
        usart_cr2_set(u, SET_MASK(13));
        usart_cr2_clear(u, CLEAR_MASK(12));
    }

    if(config->enableClock){
        usart_cr2_set(u, SET_MASK(11));//Enable Clock
    }
    usart_brr_set(u, calculate_brr_value(clock_freq(), config->br));
    usart_cr1_set(u, SET_MASK(3));//Enable Transmitter
    usart_cr1_set(u, SET_MASK(2));//Enable Receiver
    usart_cr1_set(u, SET_MASK(13));//Enable UE
}

void configure_spi(spi_t *s, SpiConfig *config)
{
    spi_cr1_clear(s, CLEAR_MASK(6));//Disable SPE
    if(config->frame == SpiDataFrame::SIXTEEN){
        spi_cr1_set(s, SET_MASK(11));
    }else{
        spi_cr1_clear(s, CLEAR_MASK(11));
    }
    if(config->edge == SpiClockEdge::RISING_3){
        //CPHA = 1 CPOL = 1
        spi_cr1_set(s, SET_MASK(0));//CPHA
        spi_cr1_set(s, SET_MASK(1));//CPOL
    }else if(config->edge == SpiClockEdge::FALLING_1){
        //CPHA = 1 CPOL = 0 
        spi_cr1_set(s, SET_MASK(0));//CPHA
        spi_cr1_clear(s, CLEAR_MASK(1));//CPOL
    }else if(config->edge == SpiClockEdge::FALLING_2){
        //CPHA = 0 CPOL = 1
        spi_cr1_clear(s, CLEAR_MASK(0));//CPHA
        spi_cr1_set(s, SET_MASK(1));//CPOL
    }else{
        //CPHA = 0 CPOL = 0
        spi_cr1_clear(s, CLEAR_MASK(0));//CPHA
        spi_cr1_clear(s, CLEAR_MASK(1));//CPOL
    }
    if(config->format == SpiDataFormat::LSB_FIRST){
        spi_cr1_set(s, SET_MASK(7));
    }else{
        spi_cr1_clear(s, CLEAR_MASK(7));
    }
    if(config->mode == SpiMode::MASTER){
        spi_cr1_set(s, SET_MASK(2));//MSTR
        spi_cr1_clear(s, ~(7u << 3));
        spi_cr1_set(s, uint32_t(config->br) << 3);//Set Baud rate
        spi_cr1_set(s, SET_MASK(8));//SSI
        spi_cr1_set(s, SET_MASK(9));//SSM
    }else{
        spi_cr1_clear(s, CLEAR_MASK(2));//SLAVE
        spi_cr1_clear(s, CLEAR_MASK(8));//SSI
        spi_cr1_set(s, SET_MASK(9));//SSM
    }
    spi_cr1_set(s, SET_MASK(6));//Enable SPE
}

void configure_i2c(i2c_t *i, I2cConfig *config)
{
    i2c_cr1_set(i, SET_MASK(15));//Enter reset
    i2c_cr1_clear(i, CLEAR_MASK(15));//Exit reset
    //Clock configuration
    auto f1 = clock_apb1_freq() / 1000000;
    auto f2 = (f1 * 1000) / (2 * config->freq_kHz);
    i2c_cr2_write(i, f1);
    i2c_ccr_write(i, f2);
    i2c_trise_write(i, f1 + 1);
    //Address Reg configuration
    uint32_t oar1_mask = 0;
    uint32_t oar2_mask = 0;
    if(config->addr_fmt == I2cAddressFormat::SEVEN){
        oar1_mask = ((config->own_addr & 0xFF) << 1) | SET_MASK(14);
    }else if(config->addr_fmt == I2cAddressFormat::DUAL){
        oar1_mask = ((config->own_addr & 0xFF) << 1) | SET_MASK(14);
        oar2_mask = (config->own_addr >> 7) | 1;
    }else{
        oar1_mask = SET_MASK(14) | SET_MASK(15) | (config->own_addr & 0x3FF);
    }
    i2c_oar1_write(i, oar1_mask);
    i2c_oar2_write(i, oar2_mask);
    i2c_cr1_set(i, SET_MASK(10) | SET_MASK(0)); //Enable PE
}
