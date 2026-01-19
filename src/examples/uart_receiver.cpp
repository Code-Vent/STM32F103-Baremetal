#include"../stm32f103/mcu.h"
#include"../apps/serial.h"

constexpr uint8_t LED_ON = 0xAB;
constexpr uint8_t LED_OFF = 0xED;

int main() {	
	auto s = STM32f103c8::get(56000000);
    OutputPin pin13;
	PortC::init(s);
	PortC::mediumSpeedOutput(13, OutputType::OpenDrain, &pin13);
    UartConfig config;
    config.baud = BaudRate::BR19200;
    config.dataBits = DataBits::EIGHT;
    config.parity = Parity::EVEN;
    config.stopBit = StopBit::ONE;
    Serial serial(Uart1{RX_ONLY}, SerialType::Asynch, &config, s);
    uint8_t data = 0;
    for(;;){
        if(serial.available()){
            data = serial.read();
        }
        
        if(data == LED_ON){
            pin13.digitalWrite(false);
        }else if(data == LED_OFF){
            pin13.digitalWrite(true);
        }else{

        }
    }
    return 0;
}