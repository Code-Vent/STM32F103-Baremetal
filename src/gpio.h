#pragma once
#include<stdint.h>

#define CONFIG_PIN_AS_PULLED_INPUT		    0x00000001
#define CONFIG_PIN_AS_LOW_SPEED_OUTPUT      0x00000002
#define CONFIG_PIN_AS_MEDIUM_SPEED_OUTPUT   0x00000004
#define CONFIG_PIN_AS_FAST_SPEED_OUTPUT     0x00000008
#define CONFIG_PIN_AS_OPEN_DRAIN            0x00000010
#define CONFIG_PIN_AS_PUSH_PULL             0x00000020
#define CONFIG_PIN_AS_ALTERNATE_FUNC        0x00000040
#define CONFIG_PIN_AS_FLOATING_INPUT        0x00000080
#define CONFIG_PIN_AS_ANALOG_INPUT          0x00000100


typedef struct gpio gpio_t;

void gpio_init(gpio_t*, uint8_t pin, uint32_t flags);
void gpio_write(gpio_t*, uint8_t pin, bool l);