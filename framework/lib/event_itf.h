#pragma once
#include "action_itf.h"
#include "common.h"
#include "object_itf.h"

interface IEventActionArg : extends IActionArg {
} ;
SET_IID( IEventActionArg, "070539ba-e3f7-4fb3-9a43-3e1de68cde3b" ) ;

interface IEventAction : extends IAction {
} ;
SET_IID(IEventAction, "6e13b45d-893e-46f9-a4fa-4006d649a56c") ;

interface IEvent {
    virtual void attach( IEventAction* action ) = 0 ;
    virtual void trigger( IEventActionArg* arg ) = 0 ;
} ;
