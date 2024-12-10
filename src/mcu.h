#pragma once
#include<stdint.h>
#include<stdint.h>
#include"clock.h"
#include"gpio.h"
#include"uart.h"
#include"libcore/types.h"
#include"def.h"



struct STM32f103c8 {
	void configure_gpio(gpio_t*, uint8_t pin, uint32_t flags)const;
	void configure_uart(uart_t*, uint32_t baud, usart_config_func, DataBits, StopBit)const;
	const STM32f103c8& enable(uint8_t bit, clock_sel_t)const;
	void write_pin(gpio_t*, uint8_t pin, bool level)const;
	static const STM32f103c8* get(uint32_t Hz=8000000, uint32_t tick_unit = 1000);
	uint32_t SYSCLK() const;
	void delay(uint32_t value) const;

	rcc_t* rcc;
	gpio_t* gpioa;
	gpio_t* gpiob;
	gpio_t* gpioc;
	uart_t* uart1;
	uart_t* uart2;
	uart_t* uart3;	
private:
	core_t core;
	STM32f103c8() {}
};