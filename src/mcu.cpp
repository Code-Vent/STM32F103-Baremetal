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

void STM32f103c8::configure_gpio(gpio_t* g, uint8_t pin, uint32_t flags)const
{
	::gpio_init(g, pin, flags);
}

void STM32f103c8::configure_uart(uart_t* u, uint32_t baud, usart_config_func f, DataBits d, StopBit s) const
{
	u->CR1 |= SET_MASK(13);//Enable Uart
	f(u, d, s);
	//Set Baud rate
	//u->BRR = (uint16_t)((72000000 / (16 * baud)));
	u->BRR = static_cast<uint16_t>(72000000 / (16 * baud));
}

const STM32f103c8& STM32f103c8::enable_peripheral(uint8_t bit, clock_sel_t clk) const
{
	auto e = ElevatePrivilegeLevel(*this);
	::clock_enable(rcc, bit, clk);
	return *this;
}

void STM32f103c8::gpio_write(gpio_t* g, uint8_t pin, bool level)const
{
	::gpio_write(g, pin, level);
}

const STM32f103c8* STM32f103c8::get(uint32_t mhz, uint32_t tick_unit)
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

		mcu.core.timer0 = reinterpret_cast<timer_t*>(0xE000E010);
		mcu.core.nvic0 = reinterpret_cast<nvic_t*>(0xE000E100);
		mcu.core.nvic1 = reinterpret_cast<nvic_t*>(0xE000EF00);
		mcu.core.scb0 = reinterpret_cast<scb_t*>(0xE000E008);
		mcu.core.mpu0 = reinterpret_cast<mpu_t*>(0xE000ED90);

		__core_ptr__ = &mcu.core;
		::clock_init(mcu.rcc, mhz);
		mcu.icore.init(clock_freq(), tick_unit);		
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

bool STM32f103c8::gpio_read(gpio_t* g, int pin) const{
    return ::gpio_read(g, pin);
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
    // Call the system function using SVC instruction
    __asm volatile (
    "mov r0, %[a0]\n"
    "mov r1, %[a1]\n"
    "mov r2, %[a2]\n"
    "mov r3, %[a3]\n"
    "mov r4, %[svcnum]\n"
    "svc 0\n"
    :
    : [a0] "r" (arg0),
      [a1] "r" (arg1),
      [a2] "r" (arg2),
      [a3] "r" (arg3),
      [svcnum] "r" (svc_num)
    : "r0", "r1", "r2", "r3", "r4", "memory"
);
}

const iCore* STM32f103c8::get_core() const{
	return &icore;
}

