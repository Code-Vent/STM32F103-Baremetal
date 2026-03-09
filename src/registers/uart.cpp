#include"uart.h"
#include"../def.h"

struct uart {
	reg_type SR;
	reg_type DR;
	reg_type BRR;
	reg_type CR1;
	reg_type CR2;
	reg_type CR3;
	reg_type GTPR;
};

void usart_cr1_set(uart_t *u, uint32_t mask)
{
	u->CR1 |= mask;
}

void usart_cr2_set(uart_t *u, uint32_t mask)
{
	u->CR2 |= mask;
}

void usart_cr1_clear(uart_t *u, uint32_t mask)
{
	u->CR1 &= mask;
}

void usart_cr2_clear(uart_t *u, uint32_t mask)
{
	u->CR2 &= mask;
}

void usart_brr_set(uart_t *u, uint32_t value)
{
	u->BRR = value;
}

bool usart_sr_read(uart_t *u, uint32_t mask)
{
    return (u->SR & mask) != 0;
}

void usart_sr_clear(uart_t *u, uint32_t mask)
{
	u->SR &= mask;
}

void usart_write(uart_t *u, char data)
{
    u->DR = data;
}

char usart_read(uart_t* u)
{
    // Read and return the received data
    return static_cast<char>(u->DR & 0xFF);
}