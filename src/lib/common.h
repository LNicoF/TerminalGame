#pragma once

#define interface  struct
#define extends    public
#define implements public

#if __cplusplus == 199711L
#define nullptr 0
#endif

#define DISABLE_COPY( cls ) \
    cls( const cls& ) ; \
    cls& operator =( const cls& )

typedef unsigned int uint ;

