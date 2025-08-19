#pragma once
#include<stdint.h>
#include"types.h"

//#define MAX_SYS_FUNC 265
#define USER_MODE 0
#define KERNEL_MODE 1


class iCore {
	public:
		iCore(core_t** core);		
	    void delay(uint32_t value)const;
		uint32_t get_ticks() const;
		void register_sysfunc(sysfunc f, uint32_t svc_num)const;
		void init(uint32_t clock_freq, uint32_t tick_unit)const;
	private:
		void tick_init(uint32_t clock_freq, uint32_t tick_unit)const;
		static void set_mode(uint32_t* args);
		core_t** core;
		static uint32_t mode;
};