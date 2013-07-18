#ifndef SERIALCHANNEL_C
#define SERIALCHANNEL_C

#include <chprintf.h>

#define SERIAL_DRIVER SD2

void serial_init(void);
int  serial_readChar(int timeoutInMilliseconds);
void serial_printChar(char character);
void serial_printString(const char* string);
void serial_printInt(int integer);

#endif
