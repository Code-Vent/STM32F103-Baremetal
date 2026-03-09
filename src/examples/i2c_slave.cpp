#include"../stm32f103/mcu.h"
#include"../drivers/serial.h"

constexpr char LED_ON = 0xAB;
constexpr char LED_OFF = 0xED;

int main() {	
	auto s = STM32f103c8::get(16000000);
    OutputPin pin13;
	PortC::init(s);
	PortC::mediumSpeedOutput(13, OutputType::OpenDrain, &pin13);
    I2cConfig config;
    config.addr_fmt = I2cAddressFormat::SEVEN;
    config.freq_kHz = 100;
    config.own_addr = 0x68;    
    I2cInterface com1;
    Serial serial(I2c1{}, &config, &com1, s);
    pin13.digitalWrite(true);
    for(;;){
        if(com1.addressFound()){
            pin13.digitalWrite(false);
        }
    }
    return 0;
}