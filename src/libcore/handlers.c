#include"types.h"

core_t* __core_ptr__;

#define __get_LR() ({ \
        uint32_t lr; \
	__asm volatile( \
		"mov %0, lr\n" \
		: "=r"(lr)); \
		lr; \
	})


void syscall_dispatcher() {
    SvCallParams s = __core_ptr__->svc_params;
    if (s.num < MAX_SYS_FUNC && __core_ptr__->kernel[s.num]) {
        __core_ptr__->kernel[s.num](s.args);
    }    
}

void SysTick_Handler() {
	__core_ptr__->ticks++;
}


void SVC_Handler() {
    syscall_dispatcher();
}