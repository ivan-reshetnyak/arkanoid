#pragma once

#include "brick.h"

namespace ark {

class engine;

namespace bricks {

class adder : public brick {
public:
  adder( double X, double Y, int ToAdd );

private:
  int ToAdd;
  virtual void onHit( engine &Engine );
};

} // End of 'bricks' namespace
} // End of 'ark' namespace
