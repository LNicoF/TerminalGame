///
///   An object environment is a set of cohexisting objects. Objects
/// can be requested to the environment through it's interfaces, and
/// the environment should be able to instantiate the objects if
/// needed and possible.
///   Every create function for an object in the environment should
/// take the environment as the first parameter, so implementations
/// can access other objects.
///   For instance, applications or shared modules may act as
/// environments.
///
#pragma once
#include "common.h"
#include "factory.h"
#include "guid.h"
#include "object_itf.h"

interface IObjectEnvironment : extends IObject {
    virtual IObject* get( const Guid& iid, const IFactory& fallbackFactory ) = 0 ;
} ;
SET_IID( IObjectEnvironment, "f1c47d06-7560-4272-a819-a77f52b22f74" ) ;

IObjectEnvironment* createObjectEnvironment( IObject* superEnv = nullptr ) ;
FACTORY( IObjectEnvironment, superEnv, createObjectEnvironment( superEnv ) ) ;

template< typename Itf >
inline Itf* get( IObjectEnvironment* objectEnv ) {
    IObject* result = objectEnv->get( Iid< Itf >::getIid(), Factory< Itf >() ) ;
    return ( Itf* )result ;
}
