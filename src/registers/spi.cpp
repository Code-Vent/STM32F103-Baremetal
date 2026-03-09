#include"spi.h"
#include"../def.h"

struct spi {
	reg_type CR1;
	reg_type CR2;
	reg_type SR;
	reg_type DR;
	reg_type CRCPR;
	reg_type RXCRCR;
	reg_type TXCRCR;
    reg_type I2SCFGR;
    reg_type I2SPR;
};

void spi_cr1_set(spi_t *s, uint32_t mask)
{
	s->CR1 |= mask;
}

void spi_cr2_set(spi_t *s, uint32_t mask)
{
	s->CR2 |= mask;
}

void spi_cr1_clear(spi_t *s, uint32_t mask)
{
	s->CR1 &= mask;
}

void spi_cr2_clear(spi_t *s, uint32_t mask)
{
	s->CR2 &= mask;
}

bool spi_sr_read(spi_t *s, uint32_t mask)
{
    return (s->SR & mask) != 0;
}

void spi_sr_clear(spi_t *s, uint32_t mask)
{
	s->SR &= mask;
}

void spi_write(spi_t *s, char16_t data)
{
	s->DR = data;
}

char16_t spi_read(spi_t *s)
{
   // Read and return the received data
   return static_cast<char16_t>(s->DR & 0xFFFF);
}
