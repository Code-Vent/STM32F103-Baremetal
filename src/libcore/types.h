#pragma once
#include<stdint.h>
#include"../def.h"


typedef struct timer timer_t;
typedef struct nvic nvic_t;
typedef struct scb scb_t;
typedef struct mpu mpu_t;


struct timer {
	reg_type CTRL;
	reg_type LOAD;
	reg_type VAL;
	reg_type CALIB;
};

struct nvic {

};

struct sbc {
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
};

struct mpu {

};

typedef struct core {	
	timer_t* timer0;
	nvic_t * nvic0;
	scb_t  * scb0;
	mpu_t  * mpu0;
	nvic_t * nvic1;
	volatile uint32_t ticks;
}core_t;



