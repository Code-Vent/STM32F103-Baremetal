#include"clock.h"



void clock_init(rcc_t* rcc) {
	rcc->CR |= 0x00010000;
	while (!(rcc->CR & 0x00020000));
	uint32_t temp = 0;
	temp &= ~0x00000003;
	temp |= 0x00000001;
	rcc->CFGR = temp;
	while (!((rcc->CFGR & 0x0000000C) == 0x00000004));
}