#pragma once

#include "color.h"

namespace ark {

class engine;

class brick {
public:
  brick( double X, double Y );
  void update( engine &Engine );
  virtual bool isDead( void );
  virtual void render( void ) const;

protected:
  color Color;

  virtual void onHit( engine &Engine );

private:
  int Durability;
  double
    X, Y,           // Center coords
    Width, Height;
};

} // End of 'ark' namespace
