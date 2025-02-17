#pragma once

#define interface  struct
#define extends    public
#define implements public

#define DISABLE_COPY( cls ) private: \
    cls( const cls& ) ; \
    cls& operator =( const cls& )

typedef unsigned int uint ;
typedef unsigned char byte ;
