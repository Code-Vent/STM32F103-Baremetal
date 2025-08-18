#include"interface.h"

sysfunc iCore::kernel[MAX_SYS_FUNC] = {0};

iCore::iCore(core_t** c, bool p)
:core(c), priviledged(p)
{
}

void iCore::register_sysfunc(sysfunc f, uint32_t svc_num){
	if(svc_num < MAX_SYS_FUNC){
		kernel[svc_num] = f;
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

void iCore::mode(bool privileged) const
{
	
}

void iCore::syscall_dispatch(uint32_t* args, uint32_t svc_num){
	if(svc_num < MAX_SYS_FUNC && kernel[svc_num]){
		kernel[svc_num](args);
	}else{

	}
}