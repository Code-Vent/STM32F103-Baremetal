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

static void common_config(uart_t* u, UartConfig* config){
	// Configure CR1
	u->CR1 &= CLEAR_MASK(13); // UE Stop
    u->CR1 |= uint32_t(config->dataBits) << 12; // M bit
	if(config->parity != NONE){
        u->CR1 |= uint32_t(config->parity) << 9; // PCE and PS bits
		u->CR1 |= SET_MASK(10);
	}
    // Configure CR2
	u->CR2 &= CLEAR_MASK(12) & CLEAR_MASK(13);
    u->CR2 |= uint32_t(config->stopBit) << 12; // STOP bits
    // Configure BRR
    u->BRR = uint16_t(config->baud); 
	u->CR1 |= SET_MASK(13); // UE Start
}

void usart_enable_tx(uart_t * u)
{
    u->CR1 |= SET_MASK(3); // TE bit
}

void usart_enable_rx(uart_t *u)
{
    u->CR1 |= SET_MASK(2); // RE bit
}

void usart_write(uart_t *u, char data)
{
    if (!u) return;
    // Wait until transmit data register is empty (TXE, bit 7 in SR)
    while (!(u->SR & SET_MASK(7)));
    // Write data to the data register
    u->DR = data;
    // Wait until transmission is complete (TC, bit 6 in SR)
    while (!(u->SR & SET_MASK(6)));
}

char usart_read(uart_t* u)
{
    if (!u) return 0;
    // Read and return the received data
    return static_cast<char>(u->DR & 0xFF);
}

bool usart_data_available(uart_t *u)
{
    return u->SR & SET_MASK(5);
}

void basic_uart_config(uart_t* u, UartConfig* config)
{
	common_config(u, config);
}

void basic_usart_config(uart_t* u, UartConfig* config)
{
	common_config(u, config);
	u->CR2 |= SET_MASK(9);
	u->CR2 |= SET_MASK(10);
	u->CR2 |= SET_MASK(11);
}