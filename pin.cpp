#include <pin.hpp>

void Pin::init(GPIO_TypeDef* port, int pin) {
    // constructor
    
    this->port = port;
    this->pin = pin;
    
    setMode(PAL_MODE_RESET);
};

void Pin::setMode(int mode) {
    palSetPadMode(port, pin, mode);
};

void Pin::setLevel(bool level) {
    palWritePad(port, pin, level);
};

void Pin::toggle(void) {
    palTogglePad(port, pin);
};

bool Pin::read(void) {
    return palReadPad(port, pin);
};
