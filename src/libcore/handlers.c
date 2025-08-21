#include"types.h"

core_t* __core_ptr__;

void SysTick_Handler() {
	__core_ptr__->ticks++;
}


void SVC_Handler() {
    SvCallParams s = __core_ptr__->svc_params;
    if (s.num < MAX_SYS_FUNC && __core_ptr__->kernel[s.num]) {
        __core_ptr__->kernel[s.num](s.args);
    }   
}