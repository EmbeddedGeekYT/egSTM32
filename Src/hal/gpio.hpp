#pragma once

#include "stm32f0xx.h"

namespace HAL
{
    /**
     * @brief Class for managing GPIO-pins
     * 
     */
    class Pin {
        public:

        /**
         * @brief Pin type enum
         * 
         */
        enum GPIOType : uint8_t {
            PushPull = 0b0,
            OpenDrain = 0b1
        };


        /**
         * @brief Pin speed enum
         * 
         */
        enum GPIOSpeed : uint8_t {
            LowSpeed = 0b00,
            MediumSpeed = 0b01,
            HighSpeed = 0b10,
            VeryHighSpeed = 0b11
        };


        /**
         * @brief Pin pull enum
         * 
         */
        enum GPIOPull : uint8_t {
            NoPull   = 0b00,
            PullUp   = 0b01,
            PullDown = 0b10
        };


        /**
         * @brief Pin constructor
         * 
         * @param gpio GPIO port
         * @param pin GPIO pin number in port
         */
        Pin(GPIO_TypeDef *gpio, uint8_t pin);


        /**
         * @brief Initialize pin as output
         * 
         * @param type Output type push-pull or open drain
         * @param speed Output speed
         */
        void InitOutput(GPIOType type = PushPull, GPIOSpeed speed = LowSpeed);


        /**
         * @brief Initialize pin as input
         * 
         * @param pull Input pull-up, pull-down or floating
         * @param speed Input speed
         */
        void InitInput(GPIOPull pull = NoPull, GPIOSpeed speed = LowSpeed);

        
        /**
         * @brief Initialize pin as an analog input
         * 
         */
        void InitAnalog();


        /**
         * @brief Initialize pin alternate function
         * 
         * @param alternate 
         * @param type 
         * @param speed 
         * @param pull 
         */
        void InitAlternate(uint8_t alternate, GPIOSpeed speed = LowSpeed, GPIOType type = PushPull, GPIOPull pull = NoPull);


        /**
         * @brief Set output high
         * 
         */
        void Set(void);


        /**
         * @brief Set output low
         * 
         */
        void Reset(void);

        /**
         * @brief Toggle output
         * 
         */
        void Toggle(void);


        /**
         * @brief Get current state of input or output pin
         * 
         * @return true 
         * @return false 
         */
        bool Get(void) const;

        operator bool() const;

        bool operator !() const;

        private:
        /**
         * @brief Enum for GPIO pin mode
         * 
         */
        enum GPIOMode : uint8_t {
            Input       = 0b00,
            Output      = 0b01,
            Alternate   = 0b10,
            Analog      = 0b11,
            Uninitialized 
        };


        /**
         * @brief Set pin mode
         * 
         * @param mode mode to set
         */
        void SetMode(GPIOMode mode);


        /**
         * @brief Set pin type
         * 
         * @param type type to set
         */
        void SetType(GPIOType type);


        /**
         * @brief Set pin speed
         * 
         * @param speed speed to set
         */
        void SetSpeed(GPIOSpeed speed);


        /**
         * @brief Set pin pull
         * 
         * @param pull pull mode to set
         */
        void SetPull(GPIOPull pull);


        /**
         * @brief Set pin alternate function
         * 
         * @param alternate Alternate function
         */
        void SetAlternate(uint8_t alternate);

        GPIO_TypeDef *m_gpio;
        uint8_t m_pin;
        GPIOMode m_mode;
    };
} // namespace HAL