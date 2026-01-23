#include"../stm32f103/mcu.h"
#include"../apps/serial.h"

constexpr char LED_ON = 0xAB;
constexpr char LED_OFF = 0xED;

int main() {	
	auto s = STM32f103c8::get();
    SerialConfig config;
    config.mode = Mode::TX_ONLY;
    config.dataBits = DataBits::EIGHT;
    config.isSynch = false;
    config.parity = Parity::EVEN;
    config.stopBit = StopBit::ONE;
    Serial serial(Uart1{}, &config, s);
    serial.begin(BaudRate::BR9600);
    for(;;){
        serial.write(LED_ON);
        s->delay_ms(200);
        serial.write(LED_OFF);
        s->delay_ms(200);
    }
    return 0;
}