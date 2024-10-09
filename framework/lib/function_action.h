#pragma once
#include "action_itf.h"
#include "common.h"
#include "object_itf.h"

class MethodAction : implements IAction {
    DISABLE_COPY( MethodAction ) ;
    SETUP_REFCOUNT() ;
    INTERFACES( IMPLEMENTED_INTERFACE( IAction ) ) ;
public:
    typedef void( *Function )( IActionArg* ) ;

private:
    Function callback ;

public:
    MethodAction( Function rCallback ) : callback( rCallback ) {
    }

    virtual ~MethodAction() {
    }

    virtual void execute( IActionArg* arg ) {
        arg->acquire() ;
        callback( arg ) ;
        arg->release() ;
    }
} ;

