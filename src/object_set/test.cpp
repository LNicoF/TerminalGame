#include <iostream>

#include "factory.h"
#include "object_itf.h"
#include "object_set_itf.h"

struct Logger {
    const char* cls ;
    Logger( const char* rCls ) : cls( rCls ) {
        std::cout << cls << " object created" << std::endl ;
    }

    virtual ~Logger() {
        std::cout << cls << " object released" << std::endl ;
    }
} ;

class Foo : extends IObject {
    Logger __l = Logger( "Foo" ) ;

    SETUP_REFCOUNT() ;
    INTERFACES() ;

    int value = 0 ;

public:
    virtual int increment() {
        return ++value ;
    }
} ;
SET_IID( Foo, "aac2d2eb-9a71-420f-8087-59f21583dce4" ) ;

Foo* createFoo() {
    return new Foo() ;
} ;

template<>
IObject* Factory< Foo >::create( class ObjectSet* ) const {
    return createFoo() ;
}


void foo( IObjectSet& ) ;
void bar( IObjectSet& ) ;

int main() {
    IObjectSet* objectSet = createObjectSet() ;

    Foo* f = get< Foo >( objectSet ) ;
    std::cout << "main(): " << f->increment() << std::endl ;
    foo( *objectSet ) ;
    bar( *objectSet ) ;

    objectSet->release() ;
}

void foo( IObjectSet& os ) {
    Foo* f = get< Foo >( &os ) ;
    std::cout << "::foo: " << f->increment() << std::endl ;
}


void bar( IObjectSet& os ) {
    Foo* f = get< Foo >( &os ) ;
    std::cout << "::bar: " << f->increment() << std::endl ;
}
