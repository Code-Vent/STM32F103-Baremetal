#pragma once
#include<stdint.h>

typedef struct uart uart_t;

enum BaudRate {
    BR9600 = 9600,
    BR19200 = 19200,
    BR38400 = 38400,
    BR57600 = 57600,
    BR115200 = 115200,
};

enum DataBits {
    EIGHT = 0,
    NINE = 1,
};

enum Parity {
    EVEN = 0,
    ODD = 1,
    NONE = 2,
};

enum StopBit {
    ONE = 0,
    HALF = 1,
    TWO = 2,
    ONE_AND_HALF = 3,
};

struct UartConfig
{
   BaudRate baud;
   DataBits dataBits;
   Parity   parity;
   StopBit stopBit;
};

void usart_enable_tx(uart_t* u);
void usart_enable_rx(uart_t* u);
void usart_write(uart_t* u, char data);
char usart_read(uart_t* u);
bool usart_data_available(uart_t* u);

void basic_uart_config(uart_t* u, UartConfig* config);
void basic_usart_config(uart_t* u, UartConfig* config);
