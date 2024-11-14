#include"mcu.h"


int main() {	
	const STM32f103c8* s = STM32f103c8::get();
	
	s->enable(4).configure_gpio(s->gpioc, 13,
		CONFIG_PIN_AS_MEDIUM_SPEED_OUTPUT |
		CONFIG_PIN_AS_OPEN_DRAIN);	
	
	for (;;) {
		s->write_pin(s->gpioc, 13, true);
		for (uint32_t i = 0; i < 400000; ++i) {
			__asm__ volatile("nop");
		}
		s->write_pin(s->gpioc, 13, false);
		for (uint32_t i = 0; i < 100000; ++i) {
			__asm__ volatile("nop");
		}
	}
	return 0;
}