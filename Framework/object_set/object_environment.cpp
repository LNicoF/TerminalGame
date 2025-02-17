#include "object_environment.h"

IObjectEnvironment* createObjectEnvironment( IObjectEnvironment* superEnv ) {
	return new ObjectEnvironment( superEnv ) ;
}
