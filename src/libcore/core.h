#pragma once
#include<stdint.h>
#include"types.h"

constexpr uint32_t USER_MODE = 1;
constexpr uint32_t KERNEL_MODE = 0;


class iCore {
	friend class STM32f103c8;
	public:
		iCore(core_t** core);		
		uint32_t get_ticks() const;		
		bool is_privileged()const;
	private:
		void register_sysfunc(sysfunc f, uint32_t svc_num)const;
		void init(bool privileged=true)const;
		void tick_init(uint32_t clock_freq, uint32_t tick_unit)const;
	 	void delay(uint32_t value)const;
		// Privileged system functions (sysfunc signature)
		static void set_mode(uint32_t* args);
		static void nvic_config(uint32_t* args);
		static void mpu_config(uint32_t* args);
		static void enter_critical(uint32_t* args);
		static void exit_critical(uint32_t* args);
		core_t** core;
		static uint32_t mode;
};