#pragma once
#include<stdint.h>
#include"types.h"

#define USER_MODE 1
#define KERNEL_MODE 0


class iCore {
	public:
		iCore(core_t** core);		
	    void delay(uint32_t value)const;
		uint32_t get_ticks() const;
		void register_sysfunc(sysfunc f, uint32_t svc_num)const;
		void init(uint32_t clock_freq, uint32_t tick_unit, bool privileged=true)const;
		bool is_privileged()const;
	private:
		void tick_init(uint32_t clock_freq, uint32_t tick_unit)const;
		// Privileged system functions (sysfunc signature)
		static void set_mode(uint32_t* args);
		static void nvic_config(uint32_t* args);
		static void mpu_config(uint32_t* args);
		static void enter_critical(uint32_t* args);
		static void exit_critical(uint32_t* args);
		core_t** core;
		static uint32_t mode;
};