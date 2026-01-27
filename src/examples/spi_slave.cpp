#include"../stm32f103/mcu.h"
#include"../apps/serial.h"

constexpr char LED_ON = 0xAB;
constexpr char LED_OFF = 0xED;

int main() {	
	auto s = STM32f103c8::get();
    OutputPin pin13;
	PortC::init(s);
	PortC::mediumSpeedOutput(13, OutputType::OpenDrain, &pin13);
    SpiConfig config;
    config.mode = SpiMode::SLAVE;
    config.edge = SpiClockEdge::FALLING;
    config.format = SpiDataFormat::LSB_FIRST;
    config.frame = SpiDataFrame::EIGHT;
    config.br = SpiBaudRate::DIV_16;
    SpiInterface com1;
    Serial serial(Spi1{}, &config, &com1, s);
    char data = 0;
    pin13.digitalWrite(true);
    for(;;){
        if(com1.available()){
            data = com1.read();
            if(data == LED_ON){
                pin13.digitalWrite(false);
            }else if(data == LED_OFF){
                pin13.digitalWrite(true);
            }
        }
    }
    return 0;
}