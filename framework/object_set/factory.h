#pragma once
#include "common.h"
#include "object_itf.h"

/// 
/// FACTORY MACRO
/// `objectEnv` is the name of the IObjectEnvironment* parameter
/// `callback` is the call to the create function, fetching the arguments throug the object environmnet.
/// Every parameter of the create function should have also a factory implementation.
///
#define FACTORY(itf, objectEnv, callback) \
	template<> class Factory< interface itf > : implements IFactory { \
	public: \
		virtual IObject* create( IObjectEnvironment* objectEnv ) const { return callback ; } \
	}

///
/// Factory Interface
/// Only implement using the FACTORY macro.
///
interface IFactory {
    virtual IObject* create( interface IObjectEnvironment* ) const = 0 ;
} ;

///
/// Factory class
/// Note that factories should not contain object construction logic,
/// only a callback to the actual create function.
///
template< typename Itf >
class Factory : implements IFactory {
public:
    virtual IObject* create( interface IObjectEnvironment* ) const {
        return nullptr ;
    }
} ;

