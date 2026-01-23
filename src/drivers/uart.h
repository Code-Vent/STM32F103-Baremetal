#pragma once
#include<stdint.h>

typedef struct uart uart_t;


void usart_cr1_set(uart_t* u, uint32_t mask);
void usart_cr2_set(uart_t* u, uint32_t mask);
void usart_cr1_clear(uart_t* u, uint32_t mask);
void usart_cr2_clear(uart_t* u, uint32_t mask);
void usart_brr_set(uart_t* u, uint32_t value);
bool usart_sr_read(uart_t* u, uint32_t mask);
void usart_sr_clear(uart_t* u, uint32_t mask);
void usart_write(uart_t* u, char data);
char usart_read(uart_t* u);
