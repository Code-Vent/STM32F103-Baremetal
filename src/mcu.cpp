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

const STM32f103c8& STM32f103c8::enable(uint8_t bit) const
{
	rcc->APB2ENR |= SET_MASK(bit);
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
		initialized = true;
	}
	return &mcu;
}
