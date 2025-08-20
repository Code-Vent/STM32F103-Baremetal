#include"core.h"

uint32_t iCore::mode = KERNEL_MODE;

bool iCore::is_privileged()const{
	return mode == KERNEL_MODE;
}

void iCore::init(uint32_t clock_freq, uint32_t tick_unit, bool privileged)const{
	(*core)->kernel[0] = iCore::set_mode;
	(*core)->kernel[1] = iCore::nvic_config;
	(*core)->kernel[2] = iCore::mpu_config;
	(*core)->kernel[3] = iCore::enter_critical;
	(*core)->kernel[4] = iCore::exit_critical;


	tick_init(clock_freq, tick_unit);
	if(!privileged){
		set_mode(USER_MODE);
	}
}

void iCore::set_mode(uint32_t* args)
{
    // Set the mode based on the argument passed
    if(args[0] == KERNEL_MODE){
        // Switch to privileged mode (CONTROL = 0)
        __asm volatile(
            "msr control, %0\n"
            "isb\n"
            :
            : "r"(0x00)
            : "memory"
        );
        mode = KERNEL_MODE;
    } else if(args[0] == USER_MODE){
        // Switch to unprivileged mode (CONTROL = 1)
        __asm volatile(
            "msr control, %0\n"
            "isb\n"
            :
            : "r"(0x01)
            : "memory"
        );
        mode = USER_MODE;
    }
}

void iCore::nvic_config(uint32_t* args) {
    // TODO: Implement NVIC enable/disable
}

void iCore::mpu_config(uint32_t* args) {
    // TODO: Implement MPU region setup
}

void iCore::enter_critical(uint32_t* args) {
    // TODO: Implement enter critical section (disable interrupts)
}

void iCore::exit_critical(uint32_t* args) {
    // TODO: Implement exit critical section (enable interrupts)
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