#pragma once
#include <string.h>

struct Guid {
    char str[ 37 ] ;

    /// Example: "03f65a15-0e37-4271-88b8-c4ef95653f4e"
    Guid( const char* guidStr ) {
        strcpy( str, guidStr ) ;
    }

    Guid( const Guid& rhs ) {
        strcpy( str, rhs.str ) ;
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
