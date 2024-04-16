#pragma once
#include "common.h"
#include "object_itf.h"
#include "display_itf.h"

interface IConsolePixel : extends IPixel {
    virtual char getSymbol() const = 0 ;
} ;
SET_IID( IConsolePixel, "cd1bc7e5-3a2c-4584-8849-08691a8a5fda" ) ;

IConsolePixel* createConsolePixel( const char& symbol ) ;

