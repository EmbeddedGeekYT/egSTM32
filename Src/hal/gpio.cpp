#include "stm32f0xx.h"
#include "gpio.hpp"
#include "rcc.hpp"

HAL::Pin::Pin(GPIO_TypeDef *gpio, uint8_t pin) {
    // ASSERT(pin <= 16)

    m_gpio = gpio;
    m_pin = pin;
    m_mode = Uninitialized;

    Clock::EnablePeripheralClock(gpio);
}


void HAL::Pin::InitOutput(GPIOType type, GPIOSpeed speed) {
    SetMode(GPIOMode::Output);
    SetType(type);
    SetPull(GPIOPull::NoPull);
    SetSpeed(speed);
}


void HAL::Pin::InitInput(GPIOPull pull, GPIOSpeed speed) {
    SetMode(GPIOMode::Input);
    SetType(GPIOType::PushPull);
    SetPull(pull);
    SetSpeed(speed);
}

void HAL::Pin::InitAnalog() {
    SetMode(GPIOMode::Analog);
    SetType(GPIOType::PushPull);
    SetPull(GPIOPull::NoPull);
    SetSpeed(GPIOSpeed::LowSpeed);
}


void HAL::Pin::InitAlternate(uint8_t alternate, GPIOSpeed speed, GPIOType type, GPIOPull pull) {
    SetMode(GPIOMode::Alternate);
    SetType(type);
    SetPull(pull);
    SetSpeed(speed);
    SetAlternate(alternate);
}


void HAL::Pin::Set(void) {
    if(m_mode != GPIOMode::Output) {
        return;
    }

    SET_BIT(m_gpio->BSRR, GPIO_BSRR_BS_0 << m_pin);
}


void HAL::Pin::Reset(void) {
    if(m_mode != GPIOMode::Output) {
        return;
    }

    SET_BIT(m_gpio->BSRR, GPIO_BSRR_BR_0 << m_pin);
}


void HAL::Pin::Toggle(void) {
    if(m_mode != GPIOMode::Output) {
        return;
    }

    if(Get()) {
        Reset();
    }
    else {
        Set();
    }
}


bool HAL::Pin::Get() const {
    if(m_mode == Input) {
        if(m_gpio->IDR & (GPIO_IDR_0 << m_pin)) {
            return true;
        }
    }
    else if (m_mode == Output) {
        if(m_gpio->ODR & (GPIO_IDR_0 << m_pin)) {
            return true;
        }
    }

    return false;
}


HAL::Pin::operator bool() const {
    return Get();
}


bool HAL::Pin::operator!() const {
    return Get() == false;
}


void HAL::Pin::SetMode(GPIOMode mode) {
    m_mode = mode;
    MODIFY_REG(m_gpio->MODER, GPIO_MODER_MODER0_Msk << (2 * m_pin), mode << (2* m_pin));
}


void HAL::Pin::SetType(GPIOType type) {
    MODIFY_REG(m_gpio->OTYPER, GPIO_OTYPER_OT_0 << m_pin, type << m_pin );
}


void HAL::Pin::SetSpeed(GPIOSpeed speed) {
    MODIFY_REG(m_gpio->OSPEEDR, GPIO_OSPEEDR_OSPEEDR0_Msk << (2*m_pin), speed << (2*m_pin));
}

void HAL::Pin::SetPull(GPIOPull pull) {
    MODIFY_REG(m_gpio->PUPDR, GPIO_PUPDR_PUPDR0_Msk << (2*m_pin), pull << (2*m_pin));
}

void HAL::Pin::SetAlternate(uint8_t alternate) {

    // ASSERT(alternate < 16);

    if(m_pin < 8) {
        MODIFY_REG(m_gpio->AFR[0], GPIO_AFRL_AFSEL0_Msk << (m_pin * 4), alternate << (m_pin * 4));
    }
    else {
        MODIFY_REG(m_gpio->AFR[1], GPIO_AFRH_AFSEL8_Msk << ((m_pin - 8) * 4), alternate << ((m_pin - 8) * 4));
    }
}