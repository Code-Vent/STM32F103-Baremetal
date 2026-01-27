#pragma once

#include<stdint.h>

typedef struct i2c i2c_t;

void i2c_cr1_set(i2c_t* i, uint32_t mask);
void i2c_cr2_set(i2c_t* i, uint32_t mask);
void i2c_oar1_set(i2c_t* i, uint32_t mask);
void i2c_oar2_set(i2c_t* i, uint32_t mask);
void i2c_cr1_clear(i2c_t* i, uint32_t mask);
void i2c_cr2_clear(i2c_t* i, uint32_t mask);
void i2c_oar1_clear(i2c_t* i, uint32_t mask);
void i2c_oar2_clear(i2c_t* i, uint32_t mask);
void i2c_brr_set(i2c_t* i, uint32_t value);
bool i2c_sr_read(i2c_t* i, uint32_t mask);
void i2c_sr_clear(i2c_t* i, uint32_t mask);
void i2c_write(i2c_t* i, char data);
char i2c_read(i2c_t* i);