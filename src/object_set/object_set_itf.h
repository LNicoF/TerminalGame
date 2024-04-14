#pragma once
#include "guid.h"
#include "object_itf.h"

interface IObjectSet : extends IObject {
    virtual IObject* get( const Guid& iid ) = 0 ;
} ;
SET_IID( IObjectSet, "1d02a4ca-3e0e-45b6-bc14-9db790cb75a4" ) ;

IObjectSet* createObjectSet() ;
