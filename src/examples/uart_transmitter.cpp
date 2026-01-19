#include"../stm32f103/mcu.h"
#include"../apps/serial.h"

constexpr uint8_t LED_ON = 0xAB;
constexpr uint8_t LED_OFF = 0xED;

int main() {	
	auto s = STM32f103c8::get(56000000);
    UartConfig config;
    config.baud = BaudRate::BR19200;
    config.dataBits = DataBits::EIGHT;
    config.parity = Parity::EVEN;
    config.stopBit = StopBit::ONE;
    Serial serial(Uart1{TX_ONLY}, SerialType::Asynch, &config, s);
    for(;;){
        serial.write(LED_ON);
        s->delay_ms(100);
        serial.write(LED_OFF);
        s->delay_ms(100);
    }
    return 0;
}