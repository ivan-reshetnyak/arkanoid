#pragma once

#include "brick.h"

namespace ark {

class engine;

namespace bricks {

class hard : public brick {
public:
  hard( double X, double Y, int Durability );
  virtual void render( void ) const override;

private:
  int MaxDurability;
};

} // End of 'bricks' namespace
} // End of 'ark' namespace
