#include"mcu.h"


int main() {	
	auto s = STM32f103c8::get(48000000, 1000000);
	
	s->enable_peripheral(4, clock_sel_t::APB2).configure_gpio(s->gpioc, 13,
		CONFIG_PIN_AS_MEDIUM_SPEED_OUTPUT |
		CONFIG_PIN_AS_OPEN_DRAIN);	
	auto core = s->get_core(false);
	
	for (;;) {
		s->gpio_write(s->gpioc, 13, true);
		core->delay(100000);
		s->gpio_write(s->gpioc, 13, false);
		core->delay(100000);
	}
	return 0;
}