#pragma once
#include "object_itf.h"

interface IActionArg : extends IObject {
} ;
SET_IID( IActionArg, "faba1848-9ed7-4a4c-8ce8-c4df6b0d2528" ) ;


interface IAction : extends IObject {
    virtual void execute( IActionArg* arg ) = 0 ;
} ;
SET_IID( IAction, "a554e252-0952-42d5-8800-25d4203cf0b9" ) ;

