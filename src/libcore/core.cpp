#include"core.h"

uint32_t iCore::mode;

void iCore::init(uint32_t clock_freq, uint32_t tick_unit)const{
	(*core)->kernel[0] = &iCore::set_mode;


	tick_init(clock_freq, tick_unit);
}

void iCore::set_mode(uint32_t* args)
{
	// Set the mode based on the argument passed
	mode = args[0];
	if(mode){
		__asm volatile(
			"cpsie i\n"
			"msr control, %0\n"
			:
			: "r"(0x03)
			: "memory"
		);
	}else{
			__asm volatile(
			"cpsie i\n"
			"msr control, %0\n"
			:
			: "r"(0x00)
			: "memory"
		);
	}
}

iCore::iCore(core_t** c)
:core(c)
{
}

void iCore::register_sysfunc(sysfunc f, uint32_t svc_num)const{
	if(svc_num < MAX_SYS_FUNC){
		(*core)->kernel[svc_num] = f;
	}
}

void iCore::tick_init(uint32_t clock_freq, uint32_t unit)const
{
	(*core)->timer0->LOAD = (clock_freq / unit) - 1u;
	(*core)->timer0->VAL = 0;
	(*core)->timer0->CTRL = SET_MASK(0) | SET_MASK(1) | SET_MASK(2);
}

void iCore::delay(uint32_t value)const
{
	uint32_t start = (*core)->ticks;
	while (((*core)->ticks - start) < value) {
	}
}

uint32_t iCore::get_ticks() const{
	return (*core)->ticks;
}