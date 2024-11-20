#include"types.h"

core_t* __core_ptr__;

void SysTick_Handler() {
	__core_ptr__->ticks++;
}