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
}

void I2cInterface::write(const char *str)
{
}
char I2cInterface::read()
{
    return 0;
}
bool I2cInterface::available()
{
    return false;
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
    if(config->edge == SpiClockEdge::RISING){
        //CPHA = 1 CPOL = 1
        spi_cr1_set(s, SET_MASK(0));//CPHA
        spi_cr1_set(s, SET_MASK(1));//CPOL
    }else{
        //CPOL = 0 CPHA = 1
        spi_cr1_set(s, SET_MASK(0));//CPHA
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
    //i2c_oar1_clear(i, 0);
    if(config->addr_fmt == I2cAddressFormat::SEVEN){
        i2c_oar1_set(i, (config->addr & 0xFF) << 1);
    }else if(config->addr_fmt == I2cAddressFormat::DUAL){
        i2c_oar1_set(i, (config->addr & 0xFF) << 1);
        i2c_oar2_set(i, ((config->addr >> 8) << 1) | 1);
    }else{
        i2c_oar1_set(i, SET_MASK(15) | (config->addr & 0x3FF));
    }

    i2c_cr2_set(i, config->freq_MHz & 0x3F);
    i2c_cr1_set(i, SET_MASK(0)); //Enable PE
}
