#include"types.h"

core_t* __core_ptr__;

void SysTick_Handler() {
	__core_ptr__->ticks++;
}

void SVC_Handler() {
	uint32_t* args;
	uint32_t svc_num;
	__asm volatile(
		"tst lr, #4\n"
		"ite eq\n"
		"mrseq %0, msp\n"
		"mrsne %0, psp\n"
		"ldr r1, [%0, #24]\n"
		"ldrh r1, [r1, #-2]\n"
		"and %1, r1, #0xFF\n"
		: "=r"(args), "=r"(svc_num)
		:
		:"r1", "memory"
	);
	__core_ptr__->svc(args, svc_num);
}