#include"../stm32f103/mcu.h"
#include"../apps/serial.h"

constexpr char LED_ON = 0xAB;
constexpr char LED_OFF = 0xED;

int main() {	
	auto s = STM32f103c8::get();
    UartConfig config;
    config.mode = UartMode::TX_ONLY;
    config.dataBits = UartDataBits::EIGHT;
    config.enableClock = false;
    config.parity = UartParity::EVEN;
    config.stopBit = UartStopBit::ONE;
    config.br = UartBaudRate::BR9600;
    UartInterface com1;
    Serial serial(Uart1{}, &config, &com1, s);
    for(;;){
        com1.write(LED_ON);
        s->delay_ms(200);
        com1.write(LED_OFF);
        s->delay_ms(200);
    }
    return 0;
}