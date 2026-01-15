#include"../stm32f103/mcu.h"
#include"../apps/pin.h"
#include"../apps/button.h"

void buttonDebouncer(){
	for(int i = 0; i < 4000; ++i){
		__asm("nop");
	}
}

int main() {	
	auto s = STM32f103c8::get(48000000, 1000000);
	OutputPin pin13;
	PortC::init(s);
	PortC::mediumSpeedOutput(13, OutputType::OpenDrain, &pin13);
	InputPin pin7;
	PortA::init(s);
	PortA::input(7, InputType::Pulled, &pin7);
	Button::init(&buttonDebouncer);
	Button btn(&pin7, PullType::DOWN);
	auto core = s->get_core();	
	pin13.digitalWrite(true);
	for (;;) {
		if(btn.isDown()){
			pin13.digitalWrite(true);
			core->delay(100000);
			pin13.digitalWrite(false);
			core->delay(100000);
		}
	}
	return 0;
}