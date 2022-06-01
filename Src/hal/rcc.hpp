#pragma once

#include "stm32f0xx.h"

namespace HAL {
    class Clock {
        public:
            static void InitSystemClockHSE();
            static void EnablePeripheralClock(GPIO_TypeDef *gpio);
    };
};
