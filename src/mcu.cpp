#include"mcu.h"
#include"libcore/interface.h"
#include<stdint.h>

static uint32_t _SYSCLK;

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

void pll_config(rcc_t* rcc, uint8_t mul, bool useHSE) {
	mul -= 2;
	if(mul & SET_MASK(0))
		rcc->CFGR |= SET_MASK(18);
	if (mul & SET_MASK(1))
		rcc->CFGR |= SET_MASK(19);
	if (mul & SET_MASK(2))
		rcc->CFGR |= SET_MASK(20);
	if (mul & SET_MASK(3))
		rcc->CFGR |= SET_MASK(21);

	if(useHSE)
		rcc->CFGR |= SET_MASK(16);
}

void clock_init(rcc_t* rcc, uint32_t mhz) {
	bool useHSE = false;
	uint8_t pll_mul = 0;
	if (mhz < 8000000u || mhz > 72000000u) {
		_SYSCLK = 8000000u;
		return;
	}
	else if(mhz < (4000000u * 9)) {
		pll_mul = (uint8_t)(mhz / 4000000u);
		_SYSCLK = pll_mul * 4000000u;
	}
	else {
		useHSE = true;
		pll_mul = (uint8_t)(mhz / 8000000u);
		_SYSCLK = pll_mul * 8000000u;
	}

	if (useHSE) {
		rcc->CR |= SET_MASK(16);//HSE ON
		while (!(rcc->CR | SET_MASK(17)));//HSE READY
	}
	
	pll_config(rcc, pll_mul, useHSE);
	rcc->CR |= SET_MASK(24);//PLL ON
	while (!(rcc->CR | SET_MASK(25)));//PLL READY
	
	rcc->CFGR |= SET_MASK(1);
}


extern "C"
{
	extern core_t* __core_ptr__;
}



const STM32f103c8* STM32f103c8::get(uint32_t mhz, uint32_t tick_unit)
{
	static STM32f103c8 mcu;
	static bool initialized = false;

	if (!initialized) {
		mcu.rcc   = reinterpret_cast<rcc_t*>(0x40021000);
		mcu.gpioa = reinterpret_cast<gpio_t*>(0x40010800);
		mcu.gpiob = reinterpret_cast<gpio_t*>(0x40010C00);
		mcu.gpioc = reinterpret_cast<gpio_t*>(0x40011000);
		mcu.uart1 = reinterpret_cast<uart_t*>(0x40013800);
		mcu.uart2 = reinterpret_cast<uart_t*>(0x40004400);
		mcu.uart3 = reinterpret_cast<uart_t*>(0x40004800);

		mcu.core.timer0 = reinterpret_cast<timer_t*>(0xE000E010);
		mcu.core.nvic0 = reinterpret_cast<nvic_t*>(0xE000E100);
		mcu.core.nvic1 = reinterpret_cast<nvic_t*>(0xE000EF00);
		mcu.core.scb0 = reinterpret_cast<scb_t*>(0xE000E008);
		mcu.core.mpu0 = reinterpret_cast<mpu_t*>(0xE000ED90);

		__core_ptr__ = &mcu.core;
		clock_init(mcu.rcc, mhz);
		iCore::tick_init(__core_ptr__, _SYSCLK, tick_unit);
		iCore::user_mode(__core_ptr__);
		initialized = true;
	}
	
	return &mcu;
}

uint32_t STM32f103c8::SYSCLK() const
{
	return _SYSCLK;
}

void STM32f103c8::delay(uint32_t value) const
{
	iCore::delay(__core_ptr__, value);
}
