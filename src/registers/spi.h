#pragma once
#include<stdint.h>

typedef struct spi spi_t;

void spi_cr1_set(spi_t* s, uint32_t mask);
void spi_cr2_set(spi_t* s, uint32_t mask);
void spi_cr1_clear(spi_t* s, uint32_t mask);
void spi_cr2_clear(spi_t* s, uint32_t mask);
//void spi_brr_set(spi_t* s, uint32_t value);
bool spi_sr_read(spi_t* s, uint32_t mask);
void spi_sr_clear(spi_t* s, uint32_t mask);
void spi_write(spi_t* s, char16_t data);
char16_t spi_read(spi_t* s);