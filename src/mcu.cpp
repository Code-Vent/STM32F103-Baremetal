#include"mcu.h"
#include<stdint.h>

extern "C"
{
	extern core_t* __core_ptr__;
}

STM32f103c8::STM32f103c8()
:icore(&__core_ptr__)
{
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

const STM32f103c8& STM32f103c8::enable_peripheral(uint8_t bit, clock_sel_t clk) const
{
	clock_enable(rcc, bit, clk);
	return *this;
}

void STM32f103c8::write_pin(gpio_t* g, uint8_t pin, bool level)const
{
	gpio_write(g, pin, level);
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
		mcu.icore.init(clock_freq(), tick_unit);		
		initialized = true;
	}
	
	return &mcu;
}

uint32_t STM32f103c8::system_clock_freq() const
{
	return clock_freq();
}

const iCore* STM32f103c8::get_core(bool privileged) const{
	
	if(privileged){
		__asm volatile(
			"mov r0, #1\n"
			"svc 0\n"
		);
	}else{
		__asm volatile(
			"mov r0, #0\n"
			"svc 0\n"
		);
	}
	return &icore;
}
