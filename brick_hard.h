#pragma once

#include "brick.h"

namespace ark {

class engine;

namespace bricks {

class hard : public brick {
public:
  hard( void );
  virtual void render( engine &Engine ) const final;
  virtual int getWeight( void ) const final;
  virtual brick * create( double X, double Y ) const final;

private:
  static int Weight;
  hard( double X, double Y, int Durability );
  int MaxDurability, DurMin, DurMax;
};

} // End of 'bricks' namespace
} // End of 'ark' namespace
