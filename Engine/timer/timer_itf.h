#pragma once
#include "object_itf.h"
#include "action_itf.h"

#define MS
#define SEC * 1000 MS
#define MIN * 60 SEC

interface ITimer : extends IObject {
	virtual bool start( const uint& intervalInMs ) = 0 ;
	virtual bool changeInterval( const uint& intervalInMs ) = 0 ;
	virtual bool stop() = 0 ;
	virtual bool isRunning() = 0 ;
};
SET_IID( ITimer, "50DAE3A0-C228-4808-905B-C40C4D315140" ) ;

ITimer* createTimer( IAction* action, IActionArg* arg ) ;

