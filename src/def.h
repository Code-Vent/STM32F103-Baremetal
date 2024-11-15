#pragma once
#include<stdint.h>

typedef volatile uint32_t reg_type;


#define SET_MASK(bit) (1u << (bit))
#define CLEAR_MASK(bit) (~(1u << (bit)))
