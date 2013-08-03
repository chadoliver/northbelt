#include <ch.hpp>
#include <hal.hpp>
#include <pin.hpp>
#include <pinArray.hpp>

PinArray::PinArray(void) {
    // pass
};

void PinArray::setGroupMode(Pin::Mode mode) {
    
    uint8_t i;
    for (i=0; i<num_pins; i++) {
        pins[i].setMode(mode);
    }
};

void PinArray::setGroupLevel(Pin::Level level) {
    
    uint8_t i;
    for (i=0; i<num_pins; i++) {
        pins[i].setLevel(level);
    }
};

void PinArray::choose(uint8_t selected) {
    
    setGroupLevel(LOW);
    pins[selected].setLevel(HIGH);
};

Pin::Level PinArray::read(uint8_t selected) {
    return pins[selected].read();
};

