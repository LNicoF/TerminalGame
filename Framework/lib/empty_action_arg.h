#pragma once

#include "action_itf.h"

class EmptyActionArg : implements IActionArg {
	SETUP_REFCOUNT() ;
	INTERFACES(
		IMPLEMENTED_INTERFACE( IActionArg )
	) ;

	DISABLE_COPY( EmptyActionArg ) ;

public:
	EmptyActionArg() {}
	virtual ~EmptyActionArg() ;
};

