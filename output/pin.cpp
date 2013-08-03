#include <ch.hpp>
#include <hal.hpp>
#include <pin.hpp>

void Pin::Pin(port, pin) {
    // constructor
    
    this->port = port;
    this->pin = pin;
    
    setMode(RESET);
};

void Pin::setMode(Mode mode) {
    palSetPadMode(port, pin, mode);
};

void Pin::setLevel(Level level) {
    palWritePad(port, pin, level)
};

void Pin::toggle(void) {
    palTogglePad(port, pin);
};

Level Pin::read(void) {
    return palReadPad(port, pin)
};