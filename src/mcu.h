#pragma once
#include<stdint.h>
#include<stdint.h>
#include"clock.h"
#include"gpio.h"
#include"uart.h"
#include"libcore/types.h"
#include"libcore/core.h"
#include"def.h"



class STM32f103c8 {
	friend class ElevatePrivilegeLevel;
	public:
		static const STM32f103c8* get(uint32_t Hz=8000000, 
			uint32_t tick_unit = 1000);		
		const iCore* get_core(bool privileged = false) const;
		void configure_gpio(gpio_t*, uint8_t pin, uint32_t flags)const;
		void configure_uart(uart_t*, uint32_t baud, usart_config_func, 
			DataBits, StopBit)const;
		const STM32f103c8& enable_peripheral(uint8_t bit, clock_sel_t)const;		
	
		uint32_t get_tick()const;
		uint32_t get_sysclk()const;
		void gpio_write(gpio_t*, uint8_t pin, bool level)const;
		bool gpio_read(gpio_t*, int pin)const;
		int uart_send(uart_t*, const char* data, int len)const;
		int uart_recv(uart_t*, char* data, int len)const;
		
		rcc_t* rcc;
		gpio_t* gpioa;
		gpio_t* gpiob;
		gpio_t* gpioc;
		uart_t* uart1;
		uart_t* uart2;
		uart_t* uart3;
		void call(uint32_t svc_num, uint32_t arg0, uint32_t arg1=0, uint32_t arg2=0, uint32_t arg3=0)const;
	private:
		STM32f103c8(const STM32f103c8&) = delete;
		STM32f103c8& operator=(const STM32f103c8&) = delete;
		mutable core_t core;
		iCore  icore;
		STM32f103c8();
};