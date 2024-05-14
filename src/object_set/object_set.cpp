#include "factory.h"
#include "object_set.h"

IObjectSet* createObjectSet() {
    return new ObjectSet ;
}
