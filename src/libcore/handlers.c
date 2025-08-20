#include"types.h"

core_t* __core_ptr__;

#define __get_LR() ({ \
        uint32_t lr; \
	__asm volatile( \
		"mov %0, lr\n" \
		: "=r"(lr)); \
		lr; \
	})


void syscall_dispatcher(uint32_t* args) {
    uint32_t svc_num = args[4];
    if (svc_num < MAX_SYS_FUNC && __core_ptr__->kernel[svc_num]) {
        __core_ptr__->kernel[svc_num](args);
    }
}

void SysTick_Handler() {
	__core_ptr__->ticks++;
}


__attribute__((naked)) void SVC_Handler() {
    __asm volatile(
        "push {lr}\n"                // Save return address
        "mrs r0, msp\n"              // r0 = MSP (main stack pointer)
        "tst lr, #4\n"               // Test bit 2 of EXC_RETURN to select stack
        "it ne\n"
        "mrsne r0, psp\n"            // If not zero, use PSP (process stack pointer)
        "bl syscall_dispatcher\n"    // Call syscall_dispatcher(args)
        "pop {pc}\n"                 // Return from exception
    );
}