#pragma once

#include "color.h"

namespace ark {

class engine;

class brick {
public:
  brick( double X, double Y );
  virtual void update( engine &Engine );
  virtual bool isDead( void ) const;
  virtual void render( engine &Engine ) const;

protected:
  color Color;
  int Durability;
  double
    X, Y,           // Center coords
    Width, Height;

  virtual void onHit( engine &Engine );
};

} // End of 'ark' namespace
