#pragma once
#include<stdint.h>

typedef volatile uint32_t reg_type;


#define CONFIG_PIN_AS_PULLED_INPUT		    0x00000001
#define CONFIG_PIN_AS_LOW_SPEED_OUTPUT      0x00000002
#define CONFIG_PIN_AS_MEDIUM_SPEED_OUTPUT   0x00000004
#define CONFIG_PIN_AS_FAST_SPEED_OUTPUT     0x00000008
#define CONFIG_PIN_AS_OPEN_DRAIN            0x00000010
#define CONFIG_PIN_AS_PUSH_PULL             0x00000020
#define CONFIG_PIN_AS_ALTERNATE_FUNC        0x00000040
#define CONFIG_PIN_AS_FLOATING_INPUT        0x00000080
#define CONFIG_PIN_AS_ANALOG_INPUT          0x00000100


#define SET_MASK(bit) (1u << (bit))
#define CLEAR_MASK(bit) (~(1u << (bit)))
