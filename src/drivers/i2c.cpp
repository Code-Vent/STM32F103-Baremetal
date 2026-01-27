#include"i2c.h"
#include"../def.h"

struct i2c {
	reg_type CR1;
	reg_type CR2;
	reg_type OAR1;
	reg_type OAR2;
	reg_type DR;
	reg_type SR1;
	reg_type SR2;
    reg_type CCR;
    reg_type TRISE;
};

void i2c_cr1_set(i2c_t *i, uint32_t mask)
{
    i->CR1 |= mask;
}

void i2c_cr2_set(i2c_t *i, uint32_t mask)
{
    i->CR2 |= mask;
}

void i2c_oar1_set(i2c_t *i, uint32_t mask)
{
    i->OAR1 |= mask;
}

void i2c_oar2_set(i2c_t *i, uint32_t mask)
{

    i->OAR2 |= mask;
}

void i2c_cr1_clear(i2c_t *i, uint32_t mask)
{
    i->CR1 &= mask;
}

void i2c_cr2_clear(i2c_t *i, uint32_t mask)
{
    i->CR2 &= mask;
}

void i2c_oar1_clear(i2c_t *i, uint32_t mask)
{
    i->OAR1 &= mask;
}

void i2c_oar2_clear(i2c_t *i, uint32_t mask)
{
    i->OAR2 &= mask;
}

bool i2c_sr_read(i2c_t *i, uint32_t mask)
{
    return false;
}

void i2c_sr_clear(i2c_t *i, uint32_t mask)
{
}

void i2c_write(i2c_t *i, char data)
{
}

char i2c_read(i2c_t *i)
{
    return static_cast<char>(i->DR & 0xFF);
}
