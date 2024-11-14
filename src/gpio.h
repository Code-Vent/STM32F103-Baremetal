#pragma once
#include<stdint.h>
#include"clock.h"

typedef struct gpio gpio_t;

void gpio_init(gpio_t*, uint8_t pin, uint32_t flags);
void gpio_write(gpio_t*, uint8_t pin, bool l);