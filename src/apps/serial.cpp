#include "serial.h"

static uint32_t calculate_brr_value(uint32_t freq, uint32_t baud){
    return (freq +(baud/2)) / baud;
}

void Serial::write(char ch)
{
    while(!usart_sr_read(u, SET_MASK(7)));//Wait for Transmitter Empty flag
    usart_write(u, ch);
}

void Serial::write(const char *str)
{
    while(*str){
        write(*str++);
    }
    while(!usart_sr_read(u, SET_MASK(6)));//Wait for Transmission Complete flag
    usart_sr_clear(u, CLEAR_MASK(6)); //Clear TC
}

char Serial::read()
{
    return usart_read(u);
}

bool Serial::available()
{
    return usart_sr_read(u, SET_MASK(5));//Read RXNE
}

void Serial::begin(BaudRate br)
{
    usart_brr_set(u, calculate_brr_value(freq, br));
    usart_cr1_set(u, SET_MASK(13));//Enable UE
}

void Serial::configure(SerialConfig *config)
{
    usart_cr1_clear(u, CLEAR_MASK(13));//Disable UE
    if(config->dataBits == DataBits::EIGHT){
        usart_cr1_clear(u, CLEAR_MASK(12));
    }else{
        usart_cr1_set(u, SET_MASK(12));
    }
    usart_cr1_clear(u, CLEAR_MASK(10));//Enable Parity
    //if(config->parity == Parity::EVEN){
    //    usart_cr1_clear(u, CLEAR_MASK(9));
    //}else{
    //    usart_cr1_set(u, SET_MASK(9));
    //}

    if(config->stopBit == StopBit::ONE){
        usart_cr2_clear(u, CLEAR_MASK(13) & CLEAR_MASK(12));
    }else{
        usart_cr2_set(u, SET_MASK(13));
        usart_cr2_clear(u, CLEAR_MASK(12));
    }

    if(config->isSynch){
        usart_cr2_set(u, SET_MASK(11));//Enable Clock
    }
    usart_cr1_set(u, SET_MASK(3));//Enable Transmitter
    usart_cr1_set(u, SET_MASK(2));//Enable Receiver
}
