#include"../stm32f103/mcu.h"
#include"../apps/pin.h"
#include"../apps/button.h"

void buttonDebouncer(){
	for(int i = 0; i < 4000; ++i){
		__asm("nop");
	}
}

int main() {	
	auto s = STM32f103c8::get(56000000);
	OutputPin pin13;
	PortC::init(s);
	PortC::mediumSpeedOutput(13, OutputType::OpenDrain, &pin13);
	InputPin pin7;
	PortA::init(s);
	PortA::input(7, InputType::Pulled, &pin7);
	Button::init(&buttonDebouncer);
	Button btn(&pin7, PullType::DOWN);
	pin13.digitalWrite(true);
	for (;;) {
		if(btn.isDown()){
			pin13.digitalWrite(true);
			s->delay_ms(100);
			pin13.digitalWrite(false);
			s->delay_ms(100);
		}
	}
	return 0;
}