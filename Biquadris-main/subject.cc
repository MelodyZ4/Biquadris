#include <set>
#include "subject.h"
#include "observer.h"

void Subject::subscribe ( Observer *newView ) {
    observers.insert( newView );
}


void Subject::unsubscribe ( Observer *formerView ) {
    observers.erase( formerView );
}


void Subject::notify () {
    for ( auto i : observers ) i->update();
}
