#include"types.h"

core_t* __core_ptr__;

#define __get_LR() ({ \
        uint32_t lr; \
	__asm volatile( \
		"mov %0, lr\n" \
		: "=r"(lr)); \
		lr; \
	})


void syscall_dispatcher(uint32_t* args, uint32_t svc_num){
	if(svc_num < MAX_SYS_FUNC && __core_ptr__->kernel[svc_num]){
		__core_ptr__->kernel[svc_num](args);
	}else{

	}
}

void SysTick_Handler() {
	__core_ptr__->ticks++;
}


__attribute__((naked)) void SVC_Handler() {
	
	__asm volatile(
		"push {lr}\n"
		"mrs r0, msp\n"
		"tst lr, #4\n"
		"it ne\n"
		"mrsne r0, psp\n"
		"ldr r1, [r0, #24]\n"
		"ldrb r1, [r1, #-2]\n"
		"bl syscall_dispatcher\n"
		"pop {pc}\n"
	);
}