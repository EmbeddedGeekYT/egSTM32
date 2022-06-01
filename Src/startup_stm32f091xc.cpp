#include "stdint.h"
#include "stm32f0xx.h"

// Constants from linker
extern uint32_t _sidata;    // Start of init data
extern uint32_t _sdata;     // Start of data
extern uint32_t _edata;     // End of data
extern uint32_t _sbss;      // Start of bss
extern uint32_t _ebss;      // End of bss
extern uint32_t _estack;    // Top of stack

// Static constructor initializator from libc
extern void __libc_init_array();

// Main program endtry point
extern int main();


// Reset Handler
void Reset_Handler() {

    // Initialize data segment
    uint32_t *dataInit = &_sidata;
    uint32_t *data = &_sdata;
    while(data < &_edata) {
        *data++ = *dataInit++;
    }

    // Initialize bss segment
    uint32_t *bss = &_sbss;
    while(bss < &_ebss) {
        *bss++ = 0;
    }

    // Initilize static constructors
    __libc_init_array();

    // Enter main program
    main();

    // Handle the case where main function returns
    while(1);
}


// Default handler for unimplemented interrupts
extern "C" void Default_Handler(void) {
    while(1);
}


// Create weak aliases for unused interupt handlers
#define WEAK_ALIAS(fcn)     __attribute__((weak, alias(fcn)))
WEAK_ALIAS("Default_Handler") void NMI_Handler(void);
WEAK_ALIAS("Default_Handler") void HardFault_Handler(void);
WEAK_ALIAS("Default_Handler") void SVC_Handler(void);
WEAK_ALIAS("Default_Handler") void PendSV_Handler(void);
WEAK_ALIAS("Default_Handler") void SysTick_Handler(void);
WEAK_ALIAS("Default_Handler") void WWDG_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void PVD_VDDIO2_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void RTC_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void FLASH_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void RCC_CRS_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void EXTI0_1_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void EXTI2_3_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void EXTI4_15_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void TSC_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void DMA1_Ch1_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void ADC1_COMP_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void TIM1_BRK_UP_TRG_COM_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void TIM1_CC_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void TIM2_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void TIM3_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void TIM6_DAC_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void TIM7_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void TIM14_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void TIM15_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void TIM16_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void TIM17_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void I2C1_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void I2C2_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void SPI1_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void SPI2_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void USART1_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void USART2_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void USART3_8_IRQHandler(void);
WEAK_ALIAS("Default_Handler") void CEC_CAN_IRQHandler(void);


// Interrupt vector table
__attribute__((section(".isr_vector"), unused))
static const void (*VectorTable[])(void) = {
    (const void (*)(void)) &_estack,
    (const void (*)(void))Reset_Handler,
    (const void (*)(void))NMI_Handler,
    (const void (*)(void))HardFault_Handler,
    (const void (*)(void))0,
    (const void (*)(void))0,
    (const void (*)(void))0,
    (const void (*)(void))0,
    (const void (*)(void))0,
    (const void (*)(void))0,
    (const void (*)(void))0,
    (const void (*)(void))SVC_Handler,
    (const void (*)(void))0,
    (const void (*)(void))0,
    (const void (*)(void))PendSV_Handler,
    (const void (*)(void))SysTick_Handler,
    (const void (*)(void))WWDG_IRQHandler,                  
    (const void (*)(void))PVD_VDDIO2_IRQHandler,
    (const void (*)(void))RTC_IRQHandler,
    (const void (*)(void))FLASH_IRQHandler,
    (const void (*)(void))RCC_CRS_IRQHandler,
    (const void (*)(void))EXTI0_1_IRQHandler,
    (const void (*)(void))EXTI2_3_IRQHandler,
    (const void (*)(void))EXTI4_15_IRQHandler,
    (const void (*)(void))TSC_IRQHandler,
    (const void (*)(void))DMA1_Ch1_IRQHandler,
    (const void (*)(void))DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler,
    (const void (*)(void))DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler,
    (const void (*)(void))ADC1_COMP_IRQHandler,
    (const void (*)(void))TIM1_BRK_UP_TRG_COM_IRQHandler,
    (const void (*)(void))TIM1_CC_IRQHandler,
    (const void (*)(void))TIM2_IRQHandler,
    (const void (*)(void))TIM3_IRQHandler,
    (const void (*)(void))TIM6_DAC_IRQHandler,
    (const void (*)(void))TIM7_IRQHandler,
    (const void (*)(void))TIM14_IRQHandler,
    (const void (*)(void))TIM15_IRQHandler,
    (const void (*)(void))TIM16_IRQHandler,
    (const void (*)(void))TIM17_IRQHandler,
    (const void (*)(void))I2C1_IRQHandler,
    (const void (*)(void))I2C2_IRQHandler,
    (const void (*)(void))SPI1_IRQHandler,
    (const void (*)(void))SPI2_IRQHandler,
    (const void (*)(void))USART1_IRQHandler,
    (const void (*)(void))USART2_IRQHandler,
    (const void (*)(void))USART3_8_IRQHandler,
    (const void (*)(void))CEC_CAN_IRQHandler
};
