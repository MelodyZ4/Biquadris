#ifndef __SUBJECT_H__
#define __SUBJECT_Hs__

#include <set>


class Observer;

class Subject {
  public:
    void subscribe( Observer* );
    void unsubscribe( Observer* );

  protected:
    void notify();

  private:
    typedef std::set< Observer* > Observers;
    Observers observers;
}; // Subject


#endif
