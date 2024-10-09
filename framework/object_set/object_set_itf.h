#pragma once
#include "common.h"
#include "factory.h"
#include "guid.h"
#include "object_itf.h"

interface IObjectSet : extends IObject {
    virtual IObject* get( const Guid& iid, const IFactory& fallbackFactory ) = 0 ;
} ;
SET_IID( IObjectSet, "f1c47d06-7560-4272-a819-a77f52b22f74" ) ;

IObjectSet* createObjectSet() ;

template< typename Itf >
inline Itf* get( IObjectSet* objectSet ) { // Maybe factory optional argument to add parameters to factories
    IObject* result = objectSet->get( Iid< Itf >::getIid(), Factory< Itf >() ) ;
    return ( Itf* )result ;
}
