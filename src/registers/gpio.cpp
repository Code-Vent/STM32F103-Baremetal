#include"gpio.h"
#include"../def.h"

struct gpio {
	reg_type CRL;
	reg_type CRH;
	reg_type IDR;
	reg_type ODR;
	reg_type BSRR;
	reg_type BRR;
	reg_type LCKR;
};

void gpio_crl_clear(gpio_t *g, uint32_t mask)
{
	g->CRL &= mask;
}

void gpio_crl_set(gpio_t *g, uint32_t mask)
{
	g->CRL |= mask;
}

void gpio_crh_clear(gpio_t *g, uint32_t mask)
{
	g->CRH &= mask;
}

void gpio_crh_set(gpio_t *g, uint32_t mask)
{
	g->CRH |= mask;
}

void gpio_write(gpio_t* g, uint8_t pin, bool l)
{
    if (!g || pin > 15) {
        return; // Invalid arguments
    }

    if (l) {
        // Use BSRR for atomic bit set
        g->BSRR = (1U << pin);
    } else {
        // Use BRR for atomic bit reset
        g->BRR = (1U << pin);
    }
}

bool gpio_read(gpio_t* g, int pin) {
    if (!g || pin < 0 || pin > 15) {
        return false; // Invalid arguments
    }
    // Return true if the pin is high, false if low
    return (g->IDR & (1 << pin)) != 0;
}