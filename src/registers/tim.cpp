#include "tim.h"
#include"../def.h"

struct tim {
	reg_type CR1;
	reg_type CR2;
	reg_type SMCR;
	reg_type DIER;
	reg_type SR;
	reg_type EGR;
	reg_type CCMR1;
    reg_type CCMR2;
    reg_type CCER;
    reg_type CNT;
    reg_type PSC;
    reg_type ARR;
    reg_type RCR;
    reg_type CCR1;
    reg_type CCR2;
    reg_type CCR3;
    reg_type CCR4;
    reg_type BDTR;
    reg_type DCR;
    reg_type DMAR;
};

void tim_cr1_set(tim_t *t, uint32_t mask)
{
}

void tim_cr2_set(tim_t *t, uint32_t mask)
{
}
