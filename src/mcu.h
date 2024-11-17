#pragma once
#include<stdint.h>
#include<stdint.h>
#include"clock.h"
#include"gpio.h"
#include"uart.h"
#include"def.h"

//Clock Sources
//HSI=8MHz, HSE=4-16MHz, PLL
// 
// 


struct STM32f103c8 {
	void configure_gpio(gpio_t*, uint8_t pin, uint32_t flags)const;
	void configure_uart(uart_t*, uint32_t baud, usart_config_func, DataBits, StopBit)const;
	const STM32f103c8& enable(uint8_t bit, clock_sel_t)const;
	void write_pin(gpio_t*, uint8_t pin, bool level)const;
	static const STM32f103c8* get(uint32_t mhz=8000000);
	static uint32_t SYSCLK() const;
	rcc_t* rcc;
	gpio_t* gpioa;
	gpio_t* gpiob;
	gpio_t* gpioc;
	uart_t* uart1;
	uart_t* uart2;
	uart_t* uart3;
private:
	STM32f103c8() {}
};