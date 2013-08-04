#ifndef SERIALCHANNEL_H_
#define SERIALCHANNEL_H_

#include <ch.hpp>
#include <hal.h>

#define SERIAL_DRIVER SD2

class SerialChannel {
    
    public:
        SerialChannel(void);
        int  readChar(int timeoutInMilliseconds);
        void printChar(char character);
        void printString(const char* string);
        void printInt(int integer);
};

#endif
