#include"clock.h"
#include"../def.h"

static uint32_t _SYSCLK;

struct rcc {
	reg_type CR;
	reg_type CFGR;
	reg_type CIR;
	reg_type APB2RSTR;
	reg_type APB1RSTR;
	reg_type AHBENR;
	reg_type APB2ENR;
	reg_type APB1ENR;
	reg_type BDCR;
	reg_type CSR;
};

void clock_enable(rcc_t* rcc, uint8_t bit, clock_sel_t clk)
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
		while (!(rcc->CR & SET_MASK(17)));//HSE READY
	}
	
	pll_config(rcc, pll_mul, useHSE);
	rcc->CR |= SET_MASK(24);//PLL ON
	while (!(rcc->CR & SET_MASK(25)));//PLL READY
	
	rcc->CFGR |= SET_MASK(1);
}

uint32_t clock_freq()
{
	return _SYSCLK;
}