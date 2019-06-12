#pragma once

#include "timer.h"
#include "color.h"

namespace ark {

class paddle {
public:
  enum class direction {
    LEFT, RIGHT
  };

  paddle( const color &Col );
  void move( direction Dir, const timer &Timer );
  void resize( double Mul );
  void modSpeed( double Mul );
  void update( const timer &Timer );
  void render( void ) const;

private:
  color Color;
  double
    X, Y,           // Center coords
    TargetWidth, Width, Height,
    Speed, ResizeTime, ResizeSpeed;

  void fit( void );
};

} // End of 'ark' namespace
