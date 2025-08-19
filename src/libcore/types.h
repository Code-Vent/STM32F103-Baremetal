#pragma once
#include<stdint.h>
#include"../def.h"


typedef struct timer {
	reg_type CTRL;
	reg_type LOAD;
	reg_type VAL;
	reg_type CALIB;
}timer_t;

typedef struct nvic {
	reg_type ISER0;
	reg_type ISER1;	
	reg_type ISER2;
	reg_type RESERVED0[29];
	reg_type ICER0;
	reg_type ICER1;
	reg_type ICER2;
	reg_type RESERVED1[29];
	reg_type ISPR0;
	reg_type ISPR1;
	reg_type ISPR2;
	reg_type RESERVED2[29];
	reg_type ICPR0;
	reg_type ICPR1;
	reg_type ICPR2;
	reg_type RESERVED3[29];
	reg_type IABR0;
	reg_type IABR1;
	reg_type IABR2;
	reg_type RESERVED4[61];	
	reg_type IPR[60];
	reg_type RESERVED5[644];
	reg_type STIR;
}nvic_t;

typedef struct scb {
	reg_type ACTRL[830];
	reg_type CPUID;
	reg_type ICSR;
	reg_type VTOR;
	reg_type AIRCR;
	reg_type SCR;
	reg_type CCR;
	reg_type SHPR1;
	reg_type SHPR2;
	reg_type SHPR3;
	reg_type SHCRS;
	reg_type CFSR;
	reg_type HFSR;
	reg_type MMAR;
	reg_type BFAR;
}scb_t;

typedef struct mpu {
	reg_type TYPER;
	reg_type CR;
	reg_type RNR;
	reg_type RBAR;
	reg_type RASR;
	reg_type RBAR_A1;
	reg_type RASR_A1;
	reg_type RBAR_A2;
	reg_type RASR_A2;
	reg_type RBAR_A3;
	reg_type RASR_A3;
}mpu_t;


typedef void (*sysfunc)(uint32_t* args);
#define MAX_SYS_FUNC 256
typedef struct core {	
	timer_t* timer0;
	nvic_t * nvic0;
	scb_t  * scb0;
	mpu_t  * mpu0;
	nvic_t * nvic1;
	volatile uint32_t ticks;
	sysfunc kernel[MAX_SYS_FUNC];
}core_t;




