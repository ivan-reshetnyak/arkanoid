#pragma once

#include "GL/freeglut.h"
#include "ball.h"
#include "engine.h"
#include "brick_hard.h"
#include "constants.h"

namespace ark {
namespace bricks {

hard::hard( double X, double Y, int Durab ) : brick(X, Y) {
  MaxDurability = Durability = Durab;
  Color = BRICK_HARD_COLOR;
}


void hard::render( void ) const {
  double
    HW = 0.5 * Width,
    HH = 0.5 * Height;
  glColor4d(Color.R, Color.G, Color.B, (double)Durability / MaxDurability);
  glRectd(X - HW, Y - HH, X + HW, Y + HH);
}

} // End of 'bricks' namespace
} // End of 'ark' namespace
