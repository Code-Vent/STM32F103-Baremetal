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

void usart_write(uart_t* u, char data)
{
    if (!u) return;

    // Enable transmitter (TE bit in CR1, bit 3)
    u->CR1 |= SET_MASK(3);

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

    // Wait until the receive data register is not empty (RXNE, bit 5 in SR)
    while (!(u->SR & SET_MASK(5)));

    // Read and return the received data
    return static_cast<char>(u->DR & 0xFF);
}

void set_stop_bit(uart_t* u, StopBit s) {
	switch (s)
	{
	case StopBit::_1:
		u->CR2 &= CLEAR_MASK(12);
		u->CR2 &= CLEAR_MASK(13);
		break;
	case StopBit::_2:
		u->CR2 &= CLEAR_MASK(12);
		u->CR2 |= SET_MASK(13);
		break;
	default:
		break;
	}
}

void set_data_bits(uart_t* u, DataBits d) {
	switch (d)
	{
	case DataBits::_8:
		u->CR2 &= CLEAR_MASK(12);
		break;
	case DataBits::_9:
		u->CR2 |= SET_MASK(12);
		break;
	default:
		break;
	}
}

void basic_uart_config(uart_t* u, DataBits d, StopBit s)
{
	set_data_bits(u, d);
	set_stop_bit(u, s);
}

void basic_usart_config(uart_t* u, DataBits d, StopBit s)
{
	set_data_bits(u, d);
	set_stop_bit(u, s);
	u->CR2 |= SET_MASK(9);
	u->CR2 |= SET_MASK(10);
	u->CR2 |= SET_MASK(11);
}

void usart_hardware_flow_config(uart_t* u, DataBits d, StopBit s)
{
	set_data_bits(u, d);
	set_stop_bit(u, s);
	u->CR2 |= SET_MASK(9);
	u->CR2 |= SET_MASK(10);
	u->CR2 |= SET_MASK(11);

	u->CR3 |= SET_MASK(4);
	u->CR3 |= SET_MASK(8);
	u->CR3 |= SET_MASK(9);
}
