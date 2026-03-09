#pragma once
#include<stdint.h>

typedef struct tim tim_t;

void tim_cr1_set(tim_t* t, uint32_t mask);
void tim_cr2_set(tim_t* t, uint32_t mask);