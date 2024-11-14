#pragma once
#include"system.h"
#include<stdint.h>


constexpr int32_t SYS_write_pin 1;

/*
int32_t syscall(int32_t number, int32_t arg1, int32_t arg2, int32_t arg3) {
	int32_t result;
	__asm volatile(
		"mov r0, %1\n\t"
		"mov r1, %2\n\t"
		"mov r2, %3\n\t"
		"mov r3, %4\n\t"
		"svc #0\n\t"
		"mov %0, r0\n\t"
		: "=r" (result)
		: "r" (number), "r" (arg1), "r" (arg2), "r" (arg3)
		: "r0", "r1", "r2"
	);
	return result;
}
*/



