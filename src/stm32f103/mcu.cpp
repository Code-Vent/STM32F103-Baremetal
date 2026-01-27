#include"mcu.h"
#include<stdint.h>

extern "C"
{
	extern core_t* __core_ptr__;
}

class ElevatePrivilegeLevel{
	public:
		ElevatePrivilegeLevel(const STM32f103c8& m)
			:mcu(m), revoke_after(false)
		{
			if(!mcu.icore.is_privileged()){
				// Elevate privilege level to kernel mode
				m.call(0, KERNEL_MODE);
				revoke_after = true;
			}
		}
		~ElevatePrivilegeLevel(){
			if(revoke_after)
				mcu.call(0, USER_MODE);
		}
	private:	
		const STM32f103c8& mcu;
		bool revoke_after;
};

STM32f103c8::STM32f103c8()
:icore(&__core_ptr__)
{
}

const STM32f103c8& STM32f103c8::enable_peripheral(uint8_t bit, clock_sel_t clk) const
{
	auto e = ElevatePrivilegeLevel(*this);
	::clock_enable(rcc, bit, clk);
	return *this;
}

void STM32f103c8::delay_ms(uint32_t value) const
{
	icore.tick_init(clock_freq(), TickUnit::ms);
	icore.delay(value);
}

void STM32f103c8::delay_us(uint32_t value) const
{
	icore.tick_init(clock_freq(), TickUnit::us);
	icore.delay(value);
}

const STM32f103c8* STM32f103c8::get(uint32_t freq_Hz)
{
	static STM32f103c8 mcu;
	static bool initialized = false;

	if (!initialized) {
		mcu.rcc   = reinterpret_cast<rcc_t*>(0x40021000);
		mcu.gpioa = reinterpret_cast<gpio_t*>(0x40010800);
		mcu.gpiob = reinterpret_cast<gpio_t*>(0x40010C00);
		mcu.gpioc = reinterpret_cast<gpio_t*>(0x40011000);
		mcu.uart1 = reinterpret_cast<uart_t*>(0x40013800);
		mcu.uart2 = reinterpret_cast<uart_t*>(0x40004400);
		mcu.uart3 = reinterpret_cast<uart_t*>(0x40004800);
		mcu.spi1 = reinterpret_cast<spi_t*>(0x40013000);
		mcu.spi2 = reinterpret_cast<spi_t*>(0x40003800);
		mcu.spi3 = reinterpret_cast<spi_t*>(0x40003C00);
		mcu.i2c1 = reinterpret_cast<i2c_t*>(0x40005400);
		mcu.i2c2 = reinterpret_cast<i2c_t*>(0x40005800);

		mcu.core.timer0 = reinterpret_cast<timer_t*>(0xE000E010);
		mcu.core.nvic0 = reinterpret_cast<nvic_t*>(0xE000E100);
		mcu.core.nvic1 = reinterpret_cast<nvic_t*>(0xE000EF00);
		mcu.core.scb0 = reinterpret_cast<scb_t*>(0xE000E008);
		mcu.core.mpu0 = reinterpret_cast<mpu_t*>(0xE000ED90);

		__core_ptr__ = &mcu.core;
		::clock_init(mcu.rcc, freq_Hz);
		mcu.icore.init();		
		initialized = true;
	}
	
	return &mcu;
}

uint32_t STM32f103c8::get_sysclk()const
{
	return ::clock_freq();
}

// Unprivileged system functions (unchanged)
uint32_t STM32f103c8::get_tick()const {
    return core.ticks;
}

int STM32f103c8::uart_send(uart_t* u, const char* data, int len) const {
    if (!u || !data || len <= 0) {
        return 0;
    }
    int sent = 0;
    for (int i = 0; i < len; ++i) {
        ::usart_write(u, data[i]);
        ++sent;
    }
    return sent;
}

int STM32f103c8::uart_recv(uart_t* u, char* data, int len) const {
    if (!u || !data || len <= 0) {
        return 0;
    }
    int received = 0;
    for (int i = 0; i < len; ++i) {
        data[i] = ::usart_read(u);
        ++received;
    }
    return received;
}

void STM32f103c8::call(
    uint32_t svc_num,
    uint32_t arg0,
    uint32_t arg1,
    uint32_t arg2,
    uint32_t arg3) const
{
    core.svc_params.num = svc_num;
	core.svc_params.args[0] = arg0;
	core.svc_params.args[1] = arg1;
	core.svc_params.args[2] = arg2;
	core.svc_params.args[3] = arg3;
	__asm volatile("svc 0\n");
}

const iCore* STM32f103c8::get_core(bool privileged) const{
	call(0, privileged? KERNEL_MODE : USER_MODE);
	return &icore;
}

