#include"gpio.h"
#include"def.h"

struct gpio {
	reg_type CRL;
	reg_type CRH;
	reg_type IDR;
	reg_type ODR;
	reg_type BSRR;
	reg_type BRR;
	reg_type LCKR;
};

void gpio_init(gpio_t* gpio, uint8_t pin, uint32_t flags) {
	reg_type* crlh = nullptr;
	if (pin < 8) {
		crlh = &gpio->CRL;
	}
	else if (pin < 16) {
		crlh = &gpio->CRH;
		pin -= 8;
	}
	else {
		return;
	}

	uint8_t b0 = 4 * pin;
	if (flags & CONFIG_PIN_AS_FLOATING_INPUT || flags & CONFIG_PIN_AS_PULLED_INPUT) {
		*crlh &= CLEAR_MASK(b0);
		*crlh &= CLEAR_MASK(b0 + 1);
		*crlh &= CLEAR_MASK(b0 + 2);
		*crlh &= CLEAR_MASK(b0 + 3);
		if (flags & CONFIG_PIN_AS_FLOATING_INPUT) {
			*crlh |= SET_MASK(b0 + 2);
		}
		else {
			*crlh |= SET_MASK(b0 + 3);
		}
		return;
	}
	else {
		*crlh |= SET_MASK(b0);
		*crlh |= SET_MASK(b0 + 1);
	}

	if(flags & CONFIG_PIN_AS_LOW_SPEED_OUTPUT)
		*crlh &= CLEAR_MASK(b0);
	if(flags & CONFIG_PIN_AS_MEDIUM_SPEED_OUTPUT)
		*crlh |= SET_MASK(b0 + 1);

	if (flags & CONFIG_PIN_AS_OPEN_DRAIN) {
		*crlh |= SET_MASK(b0 + 2);
	}
	else {
		*crlh &= CLEAR_MASK(b0 + 2);
	}

	if (flags & CONFIG_PIN_AS_ALTERNATE_FUNC) {
		*crlh |= SET_MASK(b0 + 3);
	}
	else {
		*crlh &= CLEAR_MASK(b0 + 3);
	}
}

void gpio_write(gpio_t* g_gpio, uint8_t pin, bool l)
{
	if (l)
		g_gpio->ODR |= SET_MASK(pin);
	else
		g_gpio->ODR &= CLEAR_MASK(pin);
}