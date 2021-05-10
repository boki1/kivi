#ifndef KIVI_SRC_KIVI_UTIL_VISITER_ELEMENT_HH_
#define KIVI_SRC_KIVI_UTIL_VISITER_ELEMENT_HH_

#include "visitor.hh"

class visitor_element
{
  public:
    virtual ~visitor_element ();
    virtual void accept (visitor &) = 0;

  protected:
    visitor_element ();
};

#endif // KIVI_SRC_KIVI_UTIL_VISITER_ELEMENT_HH_
