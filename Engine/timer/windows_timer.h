#pragma once
#include "windows.h"
#include "timer_itf.h"

class WindowsTimer : implements ITimer {
	SETUP_REFCOUNT() ;
	INTERFACES(
		IMPLEMENTED_INTERFACE( ITimer )
	) ;
	DISABLE_COPY( WindowsTimer ) ;

private:
	HANDLE handle ;
	bool isRunning_ ;
	struct TimerProcArg {
		IAction* action ;
		IActionArg* arg ;
	} timerProcArg ;

public:
	WindowsTimer( IObject* owner, IAction* action, IActionArg* arg ) :
		SET_OWNER( owner ),
		handle( INVALID_HANDLE_VALUE ),
		isRunning_( false ),
		timerProcArg{ action, arg }
	{
		action->acquire() ;
		arg->acquire() ;
	}

	virtual ~WindowsTimer() {
		if ( isRunning() ) {
			stop() ;
		}
		timerProcArg.arg->release() ;
		timerProcArg.action->release() ;
	}

	virtual bool start( const uint& intervalInMs ) {
		if ( isRunning() ) {
			return false ;
		}
		bool ok = CreateTimerQueueTimer(
			&handle,
			nullptr,
			&timerProc,
			( PVOID )&timerProcArg,
			intervalInMs, intervalInMs,
			WT_EXECUTEDEFAULT
		) ;
		if ( ok ) {
			isRunning_ = true ;
		}
		return ok ;
	}

	virtual bool changeInterval( const uint& intervalInMs ) {
		if ( !isRunning() ) {
			return false ;
		}
		bool ok = ChangeTimerQueueTimer( nullptr, handle, intervalInMs, intervalInMs ) ;
		return ok ;
	}

	virtual bool stop() {
		if ( !isRunning() ) {
			return false ;
		}
		bool ok = DeleteTimerQueueTimer( nullptr, handle, nullptr ) ;
		if ( ok ) {
			isRunning_ = false ;
		}
		return ok ;
	}

	virtual bool isRunning() {
		return isRunning_ ;
	}

private:

	static VOID CALLBACK timerProc( PVOID parameter, BOOLEAN ) {
		TimerProcArg* arg = ( TimerProcArg* )parameter ;
		arg->action->execute( arg->arg ) ;
	}
};

