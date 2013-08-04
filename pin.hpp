#ifndef PIN_HPP_
#define PIN_HPP_

#include <ch.hpp>
#include <hal.h>

using namespace chibios_rt;

/*
enum Mode {
    RESET = PAL_MODE_RESET,                         // After reset state. 
    UNCONNECTED = PAL_MODE_UNCONNECTED,             // Safe state for unconnected pads. 
    INPUT = PAL_MODE_INPUT,                         // Regular input high-Z pad. 
    INPUT_PULLUP = PAL_MODE_INPUT_PULLUP,           // Input pad with weak pull up resistor. 
    INPUT_PULLDOWN = PAL_MODE_INPUT_PULLDOWN,       // Input pad with weak pull down resistor. 
    INPUT_ANALOG = PAL_MODE_INPUT_ANALOG,           // Analog input mode. 
    OUTPUT_PUSHPULL = PAL_MODE_OUTPUT_PUSHPULL,     // Push-pull output pad. 
    OUTPUT_OPENDRAIN = PAL_MODE_OUTPUT_OPENDRAIN,   // Open-drain output pad.
};
*/
        
class Pin {
    
    private:
        GPIO_TypeDef* port;
        uint8_t pin;
    
    public:

        void init(GPIO_TypeDef* port, int pin);
        void setMode(int mode);
        void setLevel(bool level);
        void toggle(void);
        bool read(void);
};

#endif
