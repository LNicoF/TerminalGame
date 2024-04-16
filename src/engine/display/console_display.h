#pragma once
#include <cstdio>

#include "common.h"
#include "display_itf.h"
#include "object_itf.h"

interface IConsolePixel : extends IPixel {
    virtual char getSymbol() const = 0 ;
} ;
SET_IID( IConsolePixel, "cd1bc7e5-3a2c-4584-8849-08691a8a5fda" ) ;

IConsolePixel* createConsolePixel( const char& symbol ) ;


class Console : implements IDisplay {
    SETUP_REFCOUNT() ;
    INTERFACES(
        IMPLEMENTED_INTERFACE( IDisplay )
    ) ;
    DISABLE_COPY( Console ) ;

private:
    const uint width ;
    const uint height ;
    char* buffer ;

    char& at( uint x, uint y ) {
        return ( buffer + y * ( width + 1 ) )[ x ] ;
    }

public:
    Console( const uint& rWidth, const uint& rHeight ) :
        width( rWidth ),
        height( rHeight )
    {
        buffer = new char[ ( width + 1 ) * height ] ;
        for ( int y = 0 ; y < height ; ++y ) {
            for ( int x = 0 ; x < width ; ++x ) {
                at( x, y ) = ' ' ;
            }
            at( width, y ) = '\n' ;
        }
        at( width + 1, height ) = '\0' ;
    }

    virtual ~Console() {
        delete[] buffer ;
    }

    virtual void draw( uint x, uint y, IPixel* pixel ) {
        IConsolePixel* consolePixel = ::request< IConsolePixel >( pixel ) ;
        if ( consolePixel == nullptr ) {
            return ;
        }
        consolePixel->acquire() ;
        at( x, y ) = consolePixel->getSymbol() ;
        consolePixel->release() ;
    }

    virtual void refresh() {
        printf( "%s", buffer ) ;
        for ( int y = 0 ; y < height ; ++y ) {
            for ( int x = 0 ; x < width ; ++x ) {
                at( x, y ) = ' ' ;
            }
        }
    }
} ;

inline IDisplay* createDisplay(uint width, uint height) {
    return new Console( width, height ) ;
}

class ConsolePixel : implements IConsolePixel {
    SETUP_REFCOUNT() ;
    INTERFACES(
        IMPLEMENTED_INTERFACE( IPixel ) ;
        IMPLEMENTED_INTERFACE( IConsolePixel ) ;
    ) ;

private:
    char symbol ;

public:
    ConsolePixel( const char& rSymbol ) : symbol( rSymbol ) {
    }

    ConsolePixel( const ConsolePixel& rhs ) : symbol( rhs.symbol ) {
    }

    virtual ~ConsolePixel() {
    }

    ConsolePixel& operator=( const ConsolePixel& rhs ) {
        symbol = rhs.symbol ;
        return *this ;
    }

    virtual char getSymbol() const {
        return symbol ;
    }

    virtual operator char() {
        return symbol ;
    }
} ;

inline IConsolePixel* createConsolePixel( const char& symbol ) {
    return new ConsolePixel( symbol ) ;
}
