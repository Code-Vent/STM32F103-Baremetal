#include"mcu.h"


int main() {	
	const STM32f103c8* s = STM32f103c8::get(48000000);
	
	s->enable(4, clock_sel_t::APB2).configure_gpio(s->gpioc, 13,
		CONFIG_PIN_AS_MEDIUM_SPEED_OUTPUT |
		CONFIG_PIN_AS_OPEN_DRAIN);	
	
	for (;;) {
		s->write_pin(s->gpioc, 13, true);
		for (uint32_t i = 0; i < 800000; ++i) {
			__asm__ volatile("nop");
		}
		s->write_pin(s->gpioc, 13, false);
		for (uint32_t i = 0; i < 200000; ++i) {
			__asm__ volatile("nop");
		}
	}
	return 0;
}