#include "console_display.h"

IDisplay* createDisplay(uint width, uint height) {
    return new Console( width, height ) ;
}

IConsolePixel* createConsolePixel( const char& symbol ) {
    return new ConsolePixel( symbol ) ;
}

