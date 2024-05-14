#pragma once
#include "common.h"
#include "guid.h"

#define SET_IID( itf, iid ) \
    template<> struct Iid< interface itf > { \
        static Guid getIid() { return iid ; } \
    }

#define SETUP_REFCOUNT() \
    private: int mc_refCount = 1 ; \
    public: \
        virtual void acquire() { ++mc_refCount ; } \
        virtual void release() { if ( --mc_refCount <= 0 ) delete this ; } \

#define IMPLEMENTED_INTERFACE(itf) \
    if ( iid == Iid< itf >::getIid() ) return this ;

#define DELEGATED_INTERFACE(itf,obj) \
    if ( iid == Iid< itf >::getIid() ) return obj ;

#define INTERFACES(x) \
    public: virtual IObject* request( const Guid& iid ) { \
        IMPLEMENTED_INTERFACE(IObject) ; x; return nullptr ;\
    }

template< typename Itf >
struct Iid {
    static const char* getIid() { return 0 ; }
} ;

interface IObject {
    virtual void acquire() = 0 ;
    virtual void release() = 0 ;
    virtual IObject* request( const Guid& iid ) = 0 ;
} ;
SET_IID( IObject, "00000000-0000-0000-0000-000000000000" ) ;

template< typename Itf >
inline Itf* request( IObject* obj ) {
    return ( Itf* )obj->request( Iid< Itf >::getIid() ) ;
}

inline void releaseSafely( IObject*& obj ) {
    if ( obj == nullptr ) {
        return ;
    }
    obj->release() ;
    obj = nullptr ;
}
