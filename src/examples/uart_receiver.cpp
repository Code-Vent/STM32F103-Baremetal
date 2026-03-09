#include"../stm32f103/mcu.h"
#include"../drivers/serial.h"

constexpr char LED_ON = 0xAB;
constexpr char LED_OFF = 0xED;

int main() {	
	auto s = STM32f103c8::get();
    OutputPin pin13;
	PortC::init(s);
	PortC::mediumSpeedOutput(13, OutputType::OpenDrain, &pin13);
    UartConfig config;
    config.mode = UartMode::RX_ONLY;
    config.dataBits = UartDataBits::EIGHT;
    config.enableClock = false;
    config.parity = UartParity::EVEN;
    config.stopBit = UartStopBit::ONE;
    config.br = UartBaudRate::BR9600;
    UartInterface com1;
    Serial serial(Uart1{}, &config, &com1, s);
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