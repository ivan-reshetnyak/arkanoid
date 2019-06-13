#pragma once

#include "timer.h"
#include "color.h"

namespace ark {

class engine;

class ball {
public:
  ball( const color &Col, double X = 0, double Y = 0 );
  void resize( double Mul );
  void modSpeed( double Mul );
  void update( engine &Engine );
  void render( void ) const;
  double getX( void ) const;
  double getY( void ) const;
  void setX( double X );
  void setY( double Y );
  double getW( void ) const;
  double getH( void ) const;
  void bounceVertical( void );
  void bounceHorizontal( void );
  void bounce( double XProp, double YProp );

private:
  color Color;
  double
    X, Y,           // Center coords
    Width, Height,
    XSpeed, YSpeed;
};

} // End of 'ark' namespace
