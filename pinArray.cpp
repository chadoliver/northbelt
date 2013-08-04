#include <pinArray.hpp>

void PinArray::setGroupMode(int mode) {
    
    uint8_t i;
    for (i=0; i<NUM_PINS; i++) {
        pins[i].setMode(mode);
    }
};

void PinArray::setGroupLevel(bool level) {
    
    uint8_t i;
    for (i=0; i<NUM_PINS; i++) {
        pins[i].setLevel(level);
    }
};

void PinArray::choose(uint8_t selected) {
    
    setGroupLevel(0);
    pins[selected].setLevel(1);
};

bool PinArray::read(uint8_t selected) {
    return pins[selected].read();
};

