#ifndef PIN_ARRAY_H_
#define PIN_ARRAY_H_

// The purpose of this class is to represent a set of output pins where only one 
// pin is active at a time.

#include <ch.hpp>
#include <hal.h>
#include <pin.hpp>

#define NUM_PINS 16

using namespace chibios_rt;

class PinArray {
    
    public:
        Pin pins [NUM_PINS];
        static const uint8_t length = NUM_PINS;
        
        void setGroupMode(int mode);
        void setGroupLevel(bool level);
        void choose(uint8_t index);
        bool read(uint8_t index);
};

#endif
