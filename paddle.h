#pragma once

#include "timer.h"
#include "color.h"

namespace ark {

class engine;

class paddle {
public:
  enum class direction {
    LEFT, RIGHT
  };

  paddle( void );
  void move( direction Dir, const timer &Timer );
  void resize( double Mul );
  void modSpeed( double Mul );
  void update( const timer &Timer );
  void render( engine &Engine ) const;
  double getX( void ) const;
  double getW( void ) const;
  double getH( void ) const;

private:
  color Color;
  double
    X, Y,           // Center coords
    TargetWidth, Width, Height,
    Speed, ResizeTime, ResizeSpeed;

  void fit( void );
};

} // End of 'ark' namespace
