#pragma once

#include "color.h"

namespace ark {

class engine;

class brick {
public:
  brick( void );
  virtual ~brick( void ) = default;
  virtual void update( engine &Engine );
  virtual bool isDead( void ) const;
  virtual void render( engine &Engine ) const;
  virtual int getWeight( void ) const;
  virtual brick * create( double X, double Y ) const;

protected:
  brick( double X, double Y );
  color Color;
  int Durability;
  double X, Y;  // Center coords
  static double Width, Height;
  virtual void onHit( engine &Engine );

private:
  static int Weight;
};

} // End of 'ark' namespace
