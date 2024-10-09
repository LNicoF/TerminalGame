#pragma once
#include "common.h"
#include "object_itf.h"

/// Will only be used by object set
interface IFactory {
    virtual IObject* create( class ObjectSet* ) const = 0 ;
} ;

template< typename Itf >
class Factory : implements IFactory {
public:
    virtual IObject* create( class ObjectSet* ) const {
        return nullptr ;
    }
} ;
