#include"clock.h"
#include"../def.h"

static uint32_t _SYSCLK;
static uint32_t _APB1CLK;
static uint16_t _APB1_PRESCALER;

struct rcc {
	reg_type CR;
	reg_type CFGR;
	reg_type CIR;
	reg_type APB2RSTR;
	reg_type APB1RSTR;
	reg_type AHBENR;
	reg_type APB2ENR;
	reg_type APB1ENR;
	reg_type BDCR;
	reg_type CSR;
};

struct Config{
	uint32_t cr_mask;
    uint32_t cfgr_mask;
    uint32_t sys_clock_freq;
    uint32_t apb1_freq;
};

void clock_enable(rcc_t* rcc, uint8_t bit, clock_sel_t clk)
{
	switch (clk) {
	case clock_sel_t::AHB:
		rcc->AHBENR |= SET_MASK(bit);
		break;
	case clock_sel_t::APB1:
		rcc->APB1ENR |= SET_MASK(bit);
		break;
	case clock_sel_t::APB2:
		rcc->APB2ENR |= SET_MASK(bit);
		break;
	}	
}

void clock_start(rcc_t* rcc, Config* config){
	if ((config->cr_mask & (1 << 16)) != 0) { //HSE ON
        rcc->CR |= (1 << 16);
        while ((rcc->CR & (1 << 17)) == 0) {}
        rcc->CFGR |= (config->cfgr_mask & (1 << 17)); //PLLXTPRE
    }

    //PLL MULTIPLIER
    rcc->CFGR |= (config->cfgr_mask & (1 << 18));
    rcc->CFGR |= (config->cfgr_mask & (1 << 19));
    rcc->CFGR |= (config->cfgr_mask & (1 << 20));
    rcc->CFGR |= (config->cfgr_mask & (1 << 21));

    if ((config->cr_mask & (1 << 24)) != 0) { //PLL ON
        rcc->CR |= (1 << 24);
        while ((rcc->CR & (1 << 25)) == 0) {}
        rcc->CFGR |= (config->cfgr_mask & (1 << 16)); //PLLSRC
    }
    //SW
    rcc->CFGR |= (config->cfgr_mask & (1 << 0));
    rcc->CFGR |= (config->cfgr_mask & (1 << 1));

    //if HSE is ON switch OFF HSI
    if ((config->cr_mask & (uint32_t(1) << 16)) != 0) {
        rcc->CR &= ~uint32_t(1); //HSION = 0
    }
}

void clock_init(rcc_t* rcc, uint32_t freq_Hz) {
	Config config;
	uint32_t mul = freq_Hz >> 2;
    config.cr_mask = 0x83;
    config.cfgr_mask = 0x00;
    config.sys_clock_freq = 0;
    config.apb1_freq = 0;

	if(mul <= 1){
		//4MHz => Use HSE divide by 2
        //HSE = ON, HSI = OFF, PLL = OFF, PLLXTPRE = 1
        //Select HSE with SW bits
        config.cr_mask |= (1 << 16); //HSEON
        config.cfgr_mask |= (1 << 17) | 0x01; //PLLXTPRE|SW
        config.sys_clock_freq = 4000000;
	}else if(mul <= 13){
		//8-52MHz in steps of 4MHz
        //HSI = ON, PLL = ON, HSE = OFF, PLLSRC = 0
        //Set pllmull to (mull - 2)
        //Select PLLCLK with sw bits
        config.cr_mask |= (1 << 24); //PLLON
        config.cfgr_mask |= ((mul - 2) << 18) | 0x02; //PLLMULL|SW
        config.sys_clock_freq = mul * 4000000;
	}else{
		//56-72MHz in steps of 8MHz
        uint32_t mul1 = freq_Hz >> 3;
        //HSE = ON, PLL = ON, HSI = OFF, PLLXTPRE = 0, PLLSRC = 1
        //Set pllmull to 9
        //Select PLLCLK with sw bits
        config.cr_mask |= (1 << 16) | (1 << 24); //HSEON|PLLON
        if (mul1 < 9) {
            config.cfgr_mask |= (1 << 16) | ((mul1 - 2) << 18) | 0x02;
            config.sys_clock_freq = mul1 * 8000000;
        } else {
            config.cfgr_mask |= (1 << 16) | (0x07 << 18) | 0x02; //PLLSRC|PLLMULL|SW
            config.sys_clock_freq = 9 * 8000000;
        }
	}

	if (config.sys_clock_freq > 36000000) {
        config.cfgr_mask |= (1 << 10);
        config.apb1_freq = config.sys_clock_freq / 2;
    } else {
        config.apb1_freq = config.sys_clock_freq;
    }

	clock_start(rcc, &config);
	_SYSCLK = config.sys_clock_freq;
	_APB1CLK = config.apb1_freq;
	if ((rcc->CFGR & (1 << 10)) == 0) {
        _APB1_PRESCALER = 1;
    } else {
        _APB1_PRESCALER = 2;
    }
}

uint32_t clock_freq()
{
	return _SYSCLK;
}

uint32_t clock_apb1_freq()
{
	return _SYSCLK;
}

uint16_t clock_apb1_prescaler(){
	return _APB1_PRESCALER;
}