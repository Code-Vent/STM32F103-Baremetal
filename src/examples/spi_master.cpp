#include"../stm32f103/mcu.h"
#include"../apps/serial.h"

constexpr char LED_ON = 0xAB;
constexpr char LED_OFF = 0xED;

int main() {	
	auto s = STM32f103c8::get();
    SpiConfig config;
    config.mode = SpiMode::MASTER;
    config.edge = SpiClockEdge::FALLING;
    config.format = SpiDataFormat::LSB_FIRST;
    config.frame = SpiDataFrame::EIGHT;
    config.br = SpiBaudRate::DIV_16;
    SpiInterface com1;
    Serial serial(Spi1{}, &config, &com1, s);
    for(;;){
        com1.write(LED_ON);
        s->delay_ms(200);
        com1.write(LED_OFF);
        s->delay_ms(200);
    }
    return 0;
}