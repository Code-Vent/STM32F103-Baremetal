#include"../stm32f103/mcu.h"
#include"../apps/serial.h"

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
    bool led_value = false; 
    pin13.digitalWrite(led_value);  
    char data = 0;
    for(;;){
        if(com1.read(0x68, 0, &data)){
            s->delay_ms(1000);
            pin13.digitalWrite(false);
            while(true){}
        }
        s->delay_ms(500);
        led_value ^= true;
        pin13.digitalWrite(led_value);
    }
    return 0;
}