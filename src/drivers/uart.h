#pragma once
#include<stdint.h>

typedef struct uart uart_t;

enum class StopBit {
	_1, _2
};

enum class DataBits {
	_9, _8
};

typedef void (*usart_config_func)(uart_t* u, DataBits, StopBit);

void usart_write(uart_t* u, char data);
char usart_read(uart_t* u);

void basic_uart_config(uart_t* u, DataBits, StopBit);
void basic_usart_config(uart_t* u, DataBits, StopBit);
void usart_hardware_flow_config(uart_t* u, DataBits, StopBit);
