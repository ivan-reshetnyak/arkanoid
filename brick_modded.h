#pragma once

#include "color.h"

namespace ark {

class engine;

namespace bricks {

template<class mod_t>
class modded : public brick {
public:
  modded( double X, double Y, const color &Col ) : brick(X, Y) {
    Color = Col;
  }

protected:
  virtual void onHit( engine &Engine ) {
    Durability--;
    Engine << new mod_t();
  }
};

} // End of 'bricks' namespace
} // End of 'ark' namespace
