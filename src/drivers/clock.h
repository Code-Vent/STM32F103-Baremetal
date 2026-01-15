#pragma once 
#include<stdint.h>

typedef struct rcc rcc_t;
typedef enum { AHB, APB1, APB2 }clock_sel_t;

void clock_enable(rcc_t* rcc, uint8_t bit, clock_sel_t clk);
void clock_init(rcc_t* rcc, uint32_t mhz);
uint32_t clock_freq();