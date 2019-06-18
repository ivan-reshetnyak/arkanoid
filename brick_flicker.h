#pragma once

#include "brick.h"

namespace ark {

class engine;

namespace bricks {

class flicker : public brick {
public:
  flicker( void );
  virtual void update( engine &Engine );
  virtual void render( engine &Engine ) const override;
  virtual int getWeight( void ) const final;
  virtual brick * create( double X, double Y ) const final;

private:
  flicker( double X, double Y, double Period );
  static int Weight;
  static double PerMin, PerMax, Alpha;
  bool IsActive;
  double Period, StateTime;
};

} // End of 'bricks' namespace
} // End of 'ark' namespace
