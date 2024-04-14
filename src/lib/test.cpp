#include <iostream>

#include "guid.h"

int main() {
    Guid a = "1f170f2e-af64-4c7f-93cb-2767ad910a61" ;
    Guid b = "cb845169-96fd-4723-b7a1-6c583c1c753b" ;
    Guid c = a ;
    std::cout << a << '\n' << b << std::endl ;
    std::cout
        << ( a == a ) << '\n'
        << ( a == b ) << '\n'
        << ( b == a ) << '\n'
        << ( a == c ) << '\n'
        << ( c == a ) << '\n'
        << ( c == c ) << '\n' ;

    /// Expected:
    /// 1
    /// 0
    /// 0
    /// 1
    /// 1
    /// 1
}
