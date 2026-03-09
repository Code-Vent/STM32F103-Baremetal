#pragma once

#include<stdint.h>

typedef struct i2c i2c_t;

void i2c_cr1_set(i2c_t* i, uint32_t mask);
void i2c_cr2_set(i2c_t* i, uint32_t mask);
void i2c_cr2_write(i2c_t* i, uint32_t value);
void i2c_oar1_write(i2c_t* i, uint32_t value);
void i2c_oar2_write(i2c_t* i, uint32_t value);
void i2c_cr1_clear(i2c_t* i, uint32_t mask);
void i2c_cr2_clear(i2c_t* i, uint32_t mask);
void i2c_ccr_write(i2c_t* i, uint32_t value);
void i2c_trise_write(i2c_t* i, uint32_t value);
bool i2c_sr1_read(i2c_t* i, uint32_t mask);
bool i2c_sr2_read(i2c_t* i, uint32_t mask);
void i2c_sr1_clear(i2c_t* i, uint32_t mask);
void i2c_write(i2c_t* i, char data);
char i2c_read(i2c_t* i);