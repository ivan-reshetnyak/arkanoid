#pragma once

#include "brick.h"
#include "constants.h"

namespace ark {

class engine;

namespace bricks {

class flicker : public brick {
public:
  flicker( double X, double Y, double Period = BRICK_FLICKER_PERIOD_MIN );
  virtual void update( engine &Engine );
  virtual void render( void ) const override;

private:
  bool IsActive;
  double Period, StateTime;
};

} // End of 'bricks' namespace
} // End of 'ark' namespace
