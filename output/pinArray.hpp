#ifndef PIN_ARRAY_H_
#define PIN_ARRAY_H_

// The purpose of this class is to represent a set of output pins where only one 
// pin is active at a time.


template <uint8_t num_pins>
class PinArray {
    
    private:
        Pin pins [num_pins];
        static const uint8_t length = num_pins;
    
    public:
        void PinArray(void);
        void setGroupMode(Pin::Mode mode);
        void setGroupLevel(Pin::Level level);
        void choose(uint8_t index);
        Pin::Level read(uint8_t index);
};

#endif