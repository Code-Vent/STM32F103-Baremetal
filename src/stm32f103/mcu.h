#pragma once
#include<stdint.h>
#include<stdint.h>
#include"../drivers/clock.h"
#include"../drivers/gpio.h"
#include"../drivers/uart.h"
#include"../drivers/spi.h"
#include"../drivers/i2c.h"
#include"../libcore/types.h"
#include"../libcore/core.h"
#include"../def.h"

enum TickUnit{
	ms = 1000,
	us = 1000000
};

class STM32f103c8 {
	friend class ElevatePrivilegeLevel;
	public:
		static const STM32f103c8* get(uint32_t freq_Hz=8000000);		
		const iCore* get_core(bool privileged = false) const;
		const STM32f103c8& enable_peripheral(uint8_t bit, clock_sel_t)const;	
		void delay_ms(uint32_t value)const;
		void delay_us(uint32_t value)const;
		uint32_t get_tick()const;
		uint32_t get_sysclk()const;
		int uart_send(uart_t*, const char* data, int len)const;
		int uart_recv(uart_t*, char* data, int len)const;
		
		rcc_t* rcc;
		gpio_t* gpioa;
		gpio_t* gpiob;
		gpio_t* gpioc;
		uart_t* uart1;
		uart_t* uart2;
		uart_t* uart3;
		spi_t*  spi1;
		spi_t*  spi2;
		spi_t*  spi3;
		i2c_t*  i2c1;
		i2c_t*  i2c2;
		void call(uint32_t svc_num, uint32_t arg0, uint32_t arg1=0, uint32_t arg2=0, uint32_t arg3=0)const;
	private:
		STM32f103c8(const STM32f103c8&) = delete;
		STM32f103c8& operator=(const STM32f103c8&) = delete;
		mutable core_t core;
		iCore  icore;
		STM32f103c8();
};