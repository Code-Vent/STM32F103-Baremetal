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