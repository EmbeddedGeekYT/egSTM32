#include "stdint.h"
#include "system_stm32f0xx.h"
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

    // Run  ST system init
    SystemInit();

    // Initilize static constructors
    __libc_init_array();

    // Enter main program
    main();

    // Handle the case where main function returns
    while(1);
}


// Default handler for unimplemented interrupts
void Default_Handler(void) {
    while(1);
}



// Weak definitions of interupt handlers
__weak void NMI_Handler (void)                      { Default_Handler(); }
__weak void HardFault_Handler (void)                { Default_Handler(); }
__weak void SVC_Handler (void)                      { Default_Handler(); }
__weak void PendSV_Handler (void)                   { Default_Handler(); }
__weak void SysTick_Handler (void)                  { Default_Handler(); }
__weak void WWDG_IRQHandler (void)                  { Default_Handler(); }
__weak void PVD_VDDIO2_IRQHandler (void)            { Default_Handler(); }
__weak void RTC_IRQHandler (void)                   { Default_Handler(); }
__weak void FLASH_IRQHandler (void)                 { Default_Handler(); }
__weak void RCC_CRS_IRQHandler (void)               { Default_Handler(); }
__weak void EXTI0_1_IRQHandler (void)               { Default_Handler(); }
__weak void EXTI2_3_IRQHandler (void)               { Default_Handler(); }
__weak void EXTI4_15_IRQHandler (void)              { Default_Handler(); }
__weak void TSC_IRQHandler (void)                   { Default_Handler(); }
__weak void DMA1_Ch1_IRQHandler (void)              { Default_Handler(); }
__weak void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler (void) { Default_Handler(); }
__weak void DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler (void) { Default_Handler(); }
__weak void ADC1_COMP_IRQHandler (void)             { Default_Handler(); }
__weak void TIM1_BRK_UP_TRG_COM_IRQHandler (void)   { Default_Handler(); }
__weak void TIM1_CC_IRQHandler (void)               { Default_Handler(); }
__weak void TIM2_IRQHandler (void)                  { Default_Handler(); }
__weak void TIM3_IRQHandler (void)                  { Default_Handler(); }
__weak void TIM6_DAC_IRQHandler (void)              { Default_Handler(); }
__weak void TIM7_IRQHandler (void)                  { Default_Handler(); }
__weak void TIM14_IRQHandler  (void)                { Default_Handler(); }
__weak void TIM15_IRQHandler (void)                 { Default_Handler(); }
__weak void TIM16_IRQHandler (void)                 { Default_Handler(); }
__weak void TIM17_IRQHandler (void)                 { Default_Handler(); }
__weak void I2C1_IRQHandler (void)                  { Default_Handler(); }
__weak void I2C2_IRQHandler (void)                  { Default_Handler(); }
__weak void SPI1_IRQHandler (void)                  { Default_Handler(); }
__weak void SPI2_IRQHandler (void)                  { Default_Handler(); }
__weak void USART1_IRQHandler (void)                { Default_Handler(); }
__weak void USART2_IRQHandler (void)                { Default_Handler(); }
__weak void USART3_8_IRQHandler (void)              { Default_Handler(); }
__weak void CEC_CAN_IRQHandler(void)                { Default_Handler(); }


// Interrupt vector table
__attribute__((section(".isr_vector")))
const void (*VectorTable[])(void) = {
    (const void (*)(void)) &_estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SVC_Handler,
    0,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,                  
    PVD_VDDIO2_IRQHandler,
    RTC_IRQHandler,
    FLASH_IRQHandler,
    RCC_CRS_IRQHandler,
    EXTI0_1_IRQHandler,
    EXTI2_3_IRQHandler,
    EXTI4_15_IRQHandler,
    TSC_IRQHandler,
    DMA1_Ch1_IRQHandler,
    DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler,
    DMA1_Ch4_7_DMA2_Ch3_5_IRQHandler,
    ADC1_COMP_IRQHandler,
    TIM1_BRK_UP_TRG_COM_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM6_DAC_IRQHandler,
    TIM7_IRQHandler,
    TIM14_IRQHandler,
    TIM15_IRQHandler,
    TIM16_IRQHandler,
    TIM17_IRQHandler,
    I2C1_IRQHandler,
    I2C2_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_8_IRQHandler,
    CEC_CAN_IRQHandler
};