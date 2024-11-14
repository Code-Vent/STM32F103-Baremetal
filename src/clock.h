#pragma once 
#include<stdint.h>
#include"def.h"


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

typedef struct rcc rcc_t;
typedef enum { AHB, APB1, APB2 }clock_sel_t;

void clock_init(rcc_t*);