#pragma once

#define SET_IID( itf, iid ) \
    template<> struct Iid< interface itf > { \
        static Guid getIid() { return iid ; } \
    }

#define SETUP_REFCOUNT() \
    private: \
		int mc_refCount = 1 ; \
		IObject* mc_owner = nullptr ; \
    public: \
		virtual void acquire() { \
			++mc_refCount ; \
			if ( mc_owner != nullptr ) { mc_owner->acquire() ; } \
		} \
		virtual void release() { \
			if ( --mc_refCount == 0 ) { delete this ; return ; } \
			if ( mc_owner != nullptr ) { mc_owner->release() ; return ; } \
		}

/// Only use in member initializer lists.
#define SET_OWNER(owner) mc_owner( owner )

#define IMPLEMENTED_INTERFACE(itf) \
    if ( iid == Iid< itf >::getIid() ) return this ;

#define DELEGATED_INTERFACE(itf,obj) \
    if ( iid == Iid< itf >::getIid() ) return obj ;

#define INTERFACES(x) \
    public: virtual IObject* request( const Guid& iid ) { \
        if ( mc_owner != nullptr ) { return mc_owner->request( iid ) ; } \
        IMPLEMENTED_INTERFACE( IObject ) ; x return nullptr ; \
    }
