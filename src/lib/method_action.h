#pragma once
#include "action_itf.h"
#include "common.h"
#include "object_itf.h"

template< typename Obj >
class MethodAction : implements IAction {
    DISABLE_COPY( MethodAction ) ;
    SETUP_REFCOUNT() ;
    INTERFACES( IMPLEMENTED_INTERFACE( IAction ) ) ;
public:
    typedef void( Obj::*Method )( IActionArg* ) ;

private:
    Obj* obj ;
    Method callback ;

public:
    MethodAction( Obj rObj, Method rCallback ) : obj( rObj ), callback( rCallback ) {
    }

    virtual ~MethodAction() {
    }

    virtual void execute( IActionArg* arg ) {
        arg->acquire() ;
        ( obj->*callback )( arg ) ;
        arg->release() ;
    }
} ;


