#include "console_pixel_itf.h"
#include "display_itf.h"
#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <unistd.h>

void writeText(
    IDisplay* display,
    uint x, uint y,
    const char* str
) {
    display->acquire() ;
    for ( int i = 0 ; str[i] ; ++i ) {
        IPixel* pixel = createConsolePixel( str[i] ) ;
        display->draw( x + i, y, pixel ) ;
        pixel->release() ;
    }
    display->release() ;
}

int main() {
    winsize ws ;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws ) ;

    IDisplay* display = createDisplay(ws.ws_col, ws.ws_row) ;
    IPixel* hBorder = createConsolePixel( '_' ) ;
    IPixel* vBorder = createConsolePixel( '|' ) ;
    IPixel* blank = createConsolePixel( ' ' ) ;

    const uint baseLine = 2 ;

    for ( int x = 1 ; x + 1 < ws.ws_col ; ++x ) {
        display->draw( x, baseLine,      hBorder ) ;
        display->draw( x, ws.ws_row - 1, hBorder ) ;
    }
    for ( int y = baseLine + 1 ; y < ws.ws_row ; ++y ) {
        display->draw( 0,             y, vBorder ) ;
        display->draw( ws.ws_col - 1, y, vBorder ) ;
    }

    writeText( display, 1, 1, "HP: ♥ ♥ ♥" ) ;

    display->refresh() ;

    hBorder->release() ;
    vBorder->release() ;
    display->release() ;
}
