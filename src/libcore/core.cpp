#include"types.h"
#include"interface.h"




void iCore::tick_init(core_t* c, uint32_t clock_freq, uint32_t unit)
{
	c->timer0->LOAD = (clock_freq / unit) - 1u;
	c->timer0->VAL = 0;
	c->timer0->CTRL = SET_MASK(0) | SET_MASK(1) | SET_MASK(2);
}

void iCore::delay(core_t* c, uint32_t value)
{
	uint32_t start = c->ticks;
	while ((c->ticks - start) < value) {
	}
}

void iCore::user_mode(core_t* c)
{
}
