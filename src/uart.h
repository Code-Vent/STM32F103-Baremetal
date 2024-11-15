#pragma once
#include<stdint.h>
#include"def.h"

struct uart {
	reg_type SR;
	reg_type DR;
	reg_type BRR;
	reg_type CR1;
	reg_type CR2;
	reg_type CR3;
	reg_type GTPR;
};

typedef struct uart uart_t;


enum class StopBit {
	_1, _2
};

enum class DataBits {
	_9, _8
};

typedef void (*usart_config_func)(uart_t* u, DataBits, StopBit);

void usart_write(uart_t* u, char* data);

void basic_uart_config(uart_t* u, DataBits, StopBit);
void basic_usart_config(uart_t* u, DataBits, StopBit);
void usart_hardware_flow_config(uart_t* u, DataBits, StopBit);
