#include "rcc.hpp"
#include "gpio.hpp"

static HAL::Pin Led(GPIOA, 0);

int main(void)
{
    HAL::Clock::InitSystemClockHSE();
    Led.InitOutput();


    while (1) {
        for(int32_t delay = 100000; delay; delay++);
        Led.Toggle();
    }
  
}
