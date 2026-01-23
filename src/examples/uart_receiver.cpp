#include"../stm32f103/mcu.h"
#include"../apps/serial.h"

constexpr char LED_ON = 0xAB;
constexpr char LED_OFF = 0xED;

int main() {	
	auto s = STM32f103c8::get();
    OutputPin pin13;
	PortC::init(s);
	PortC::mediumSpeedOutput(13, OutputType::OpenDrain, &pin13);
    SerialConfig config;
    config.mode = Mode::RX_ONLY;
    config.dataBits = DataBits::EIGHT;
    config.isSynch = false;
    config.parity = Parity::EVEN;
    config.stopBit = StopBit::ONE;
    Serial serial(Uart1{}, &config, s);
    serial.begin(BaudRate::BR9600);
    char data = 0;
    pin13.digitalWrite(true);
    for(;;){
        if(serial.available()){
            data = serial.read();
            if(data == LED_ON){
                pin13.digitalWrite(false);
            }else if(data == LED_OFF){
                pin13.digitalWrite(true);
            }
        }
    }
    return 0;
}