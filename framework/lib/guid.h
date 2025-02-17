#pragma once
#include "common.h"
#include <string.h>

struct Guid {
    static const int STR_SIZE = 37 ;
    char str[ STR_SIZE ] ;

    /// Example: "03f65a15-0e37-4271-88b8-c4ef95653f4e"
    Guid( const char* guidStr ) : indexCache( 0 ) {
        strcpy_s( str, STR_SIZE, guidStr ) ;
    }

    Guid( const Guid& rhs ) : indexCache( rhs.indexCache ) {
        strcpy_s( str, STR_SIZE, rhs.str ) ;
    }

    Guid& operator=( const Guid& rhs ) {
        strcpy_s( str, STR_SIZE, rhs.str ) ;
        indexCache = rhs.indexCache ;
        return *this ;
    }

    virtual ~Guid() {
    }

    operator const char*() {
        return str ;
    }

    /**
     * returns the first 4 bytes segment
     */
    uint getIndex() const {
        if ( indexCache != 0 ) {
            return indexCache ;
        }
        uint index = 0 ;
        for ( int i = 0 ; i < 8 ; ++i ) {
            index <<= 4 ;
            index += hexToInt( str[ i ] ) ;
        }
        return indexCache = index ;
    }

private:
    mutable uint indexCache ;

    byte hexToInt( const char& hex ) const {
        if ( hex - '0' < 10 ) {
            return hex - '0' ;
        }
        if ( hex - 'a' <= 'f' - 'a' ) {
            return 10 + hex - 'a' ;
        }
        return 10 + hex - 'A' ;
    }
} ;

#ifdef _GLIBCXX_OSTREAM
std::ostream& operator<<( std::ostream& stream, const Guid& guid ) {
    stream << guid.str ;
    return stream ;
}
#endif

inline bool operator==( const Guid& lhs, const Guid& rhs ) {
    return strcmp( lhs.str, rhs.str ) == 0 ;
}
