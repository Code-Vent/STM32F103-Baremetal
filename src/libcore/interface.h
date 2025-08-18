#pragma once
#include<stdint.h>
#include"types.h"

#define MAX_SYS_FUNC 265

typedef void (*sysfunc)(uint32_t* args);

class iCore {
	public:
		iCore(core_t** core, bool privileged = true);
		void tick_init(uint32_t clock_freq, uint32_t tick_unit)const;
	    void delay(uint32_t value)const;
		uint32_t get_ticks() const;
		void mode(bool priviledged) const;
		static void syscall_dispatch(uint32_t* args, uint32_t svc_num);
		void register_sysfunc(sysfunc f, uint32_t svc_num);
	private:
		core_t** core;
		bool priviledged;
		static sysfunc kernel[MAX_SYS_FUNC];
};