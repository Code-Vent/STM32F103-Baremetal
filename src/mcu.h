#pragma once
#include<stdint.h>
#include<stdint.h>
#include"clock.h"
#include"gpio.h"
#include"def.h"


struct STM32f103c8 {
	void configure_gpio(gpio_t*, uint8_t pin, uint32_t flags)const;
	const STM32f103c8& enable(uint8_t bit)const;
	void write_pin(gpio_t*, uint8_t pin, bool level)const;
	static const STM32f103c8* get();

	rcc_t* rcc;
	gpio_t* gpioa;
	gpio_t* gpiob;
	gpio_t* gpioc;

private:
	STM32f103c8() {}
};