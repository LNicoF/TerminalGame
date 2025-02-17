#include "windows_timer.h"

ITimer* createTimer( IAction* action, IActionArg* arg ) {
	return new WindowsTimer( action, arg ) ;
}

