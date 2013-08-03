#ifndef SERIALCHANNEL_H_
#define SERIALCHANNEL_H_

#include <chprintf.h>

#define SERIAL_DRIVER SD2

class SerialChannel {
    
    private:
        static const SerialConfig config;
    
    public:
        void SerialChannel(SerialDriver driver);
        int  readChar(int timeoutInMilliseconds);
        void printChar(char character);
        void printString(const char* string);
        void printInt(int integer);
};

#endif