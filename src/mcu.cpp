#include"mcu.h"
#include<stdint.h>

extern "C" {

	void SystemInit(void) {
		//clock_init(inst.rcc);
	}

	void SVC_Handler(void) {
		
	}
}

void STM32f103c8::configure_gpio(gpio_t* g, uint8_t pin, uint32_t flags)const
{
	gpio_init(g, pin, flags);
}

void STM32f103c8::configure_uart(uart_t* u, uint32_t baud, usart_config_func f, DataBits d, StopBit s) const
{
	u->CR1 |= SET_MASK(13);//Enable Uart
	f(u, d, s);
	//Set Baud rate
	u->BRR = (uint16_t)((72000000 / (16 * baud)));
}

const STM32f103c8& STM32f103c8::enable(uint8_t bit, clock_sel_t clk) const
{
	switch (clk) {
	case clock_sel_t::AHB:
		rcc->AHBENR |= SET_MASK(bit);
		break;
	case clock_sel_t::APB1:
		rcc->APB1ENR |= SET_MASK(bit);
		break;
	case clock_sel_t::APB2:
		rcc->APB2ENR |= SET_MASK(bit);
		break;
	}	
	return *this;
}

void STM32f103c8::write_pin(gpio_t* g, uint8_t pin, bool level)const
{
	gpio_write(g, pin, level);
}

const STM32f103c8* STM32f103c8::get()
{
	static STM32f103c8 mcu;
	static bool initialized = false;

	if (!initialized) {
		mcu.rcc = reinterpret_cast<rcc_t*>(0x40021000);
		mcu.gpioa = reinterpret_cast<gpio_t*>(0x40010800);
		mcu.gpiob = reinterpret_cast<gpio_t*>(0x40010C00);
		mcu.gpioc = reinterpret_cast<gpio_t*>(0x40011000);
		mcu.uart1 = reinterpret_cast <uart_t*>(0x40013800);
		mcu.uart2 = reinterpret_cast <uart_t*>(0x40004400);
		mcu.uart3 = reinterpret_cast <uart_t*>(0x40004800);
		initialized = true;
	}
	return &mcu;
}
