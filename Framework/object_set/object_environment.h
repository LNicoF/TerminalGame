#pragma once
#include "common.h"
#include "factory.h"
#include "guid.h"
#include "object_itf.h"
#include "object_environment_itf.h"

#include <list>
#include <unordered_map>
#include <utility>

///
///   There should be support for objects taken from dynamic libraries,
/// and a dynamic choice of what librarie will provide the object.
///
class ObjectEnvironment : implements IObjectEnvironment {
    DISABLE_COPY( ObjectEnvironment ) ;
    SETUP_REFCOUNT() ;
    INTERFACES(
        IMPLEMENTED_INTERFACE( IObjectEnvironment ) ;
		return findInstance( iid ) ;
    ) ;

private:
    typedef std::unordered_map<
        uint,
        std::list< std::pair< Guid, IObject* > >
    > HashMap ;
    typedef HashMap::mapped_type::iterator ListIterator ;

    HashMap hashmap ;

public:
    ObjectEnvironment( IObject* owner = nullptr ) : SET_OWNER( owner ) {
    }

    virtual ~ObjectEnvironment() {
        releaseObjects() ;
    }

    virtual IObject* get( const Guid& iid, const IFactory& fallbackFactory ) {
        IObject* obj = findInstance( iid ) ;
        if ( obj != nullptr ) {
            return obj ;
        }
        return createInstance( iid, fallbackFactory ) ;
    }

private:
    IObject* findInstance( const Guid& iid ) {
        if ( hashmap.count( iid.getIndex() ) == 0 ) {
            return nullptr ;
        }
        HashMap::mapped_type& list = hashmap[ iid.getIndex() ] ;
        for ( ListIterator i = list.begin() ; i != list.end() ; ++i ) {
            const Guid& guid = i->first ;
            if ( guid == iid ) {
                return i->second ;
            }
        }
        return nullptr ;
    }

    IObject* createInstance( const Guid& iid, const IFactory& factory ) {
        IObject* instance = factory.create( this ) ;
        if ( instance == nullptr ) {
            return nullptr ;
        }
        set( iid, instance ) ;
        return instance ;
    }

    void set( const Guid& iid, IObject* obj ) {
        hashmap[ iid.getIndex() ].push_back( std::make_pair( iid, obj ) ) ;
    }

    void releaseObjects() {
        for ( HashMap::iterator i = hashmap.begin() ; i != hashmap.end() ; ++i ) {
            HashMap::mapped_type& list = i->second ;
            for ( ListIterator j = list.begin() ; j != list.end() ; ++j ) {
                IObject*& obj = j->second ;
                if ( obj == nullptr ) {
                    continue ;
                }
                releaseSafely( obj ) ;
            }
        }
    }
} ;

