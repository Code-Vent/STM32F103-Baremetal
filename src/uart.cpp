#include"uart.h"


void usart_write(uart_t* u, char* data)
{
	//set TE bit in cr1
	u->CR1 |= SET_MASK(3);
	while (data) {
		if (u->SR & SET_MASK(7)) {//Transmitter empty
			//Write Data
			u->DR = *data++;
		}
	}
	while (!(u->SR & SET_MASK(6))); //Transfer not complete
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
