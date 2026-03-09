#include"../stm32f103/mcu.h"
#include"../drivers/pin.h"

struct Tim_x{};

struct Tim1 : Tim_x{
    typedef PortB SerialPort; 
    static constexpr uint8_t mosi_pin = 15;
    static constexpr uint8_t miso_pin = 14;
    static constexpr uint8_t clk_pin = 13;
    static constexpr uint8_t nss_pin = 12;
};