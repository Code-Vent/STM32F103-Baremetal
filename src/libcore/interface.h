#pragma once
#include<stdint.h>


struct iCore {
	static void tick_init(core_t*, uint32_t clock_freq, uint32_t tick_unit);
	static void delay(core_t*, uint32_t value);
	static void user_mode(core_t*);
};