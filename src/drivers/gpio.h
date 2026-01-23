#pragma once
#include<stdint.h>

typedef struct gpio gpio_t;

void gpio_crl_clear(gpio_t*, uint32_t mask);
void gpio_crl_set(gpio_t*, uint32_t mask);
void gpio_crh_clear(gpio_t*, uint32_t mask);
void gpio_crh_set(gpio_t*, uint32_t mask);
void gpio_write(gpio_t*, uint8_t pin, bool l);
bool gpio_read(gpio_t* g, int pin);