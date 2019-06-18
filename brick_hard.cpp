#pragma once

#include <cstdlib>

#include <fstream>

#include "GL/freeglut.h"
#include "ball.h"
#include "engine.h"
#include "brick_hard.h"

namespace ark {
namespace bricks {

int hard::Weight = 0;

hard::hard( void ) {
  std::ifstream File("settings/brick_hard");
  File >> Weight >> Color.R >> Color.G >> Color.B
       >> DurMin >> DurMax;
}

hard::hard( double X, double Y, int Durab ) : brick(X, Y) {
  std::ifstream File("settings/brick_hard");
  File >> Weight >> Color.R >> Color.G >> Color.B;

  MaxDurability = Durability = Durab;
}

void hard::render( engine &Engine ) const {
  double
    HW = 0.5 * Width,
    HH = 0.5 * Height;
  glColor4d(Color.R, Color.G, Color.B, (double)Durability / MaxDurability);
  glRectd(X - HW, Y - HH, X + HW, Y + HH);
}

int hard::getWeight( void ) const {
  return Weight;
}

brick * hard::create( double X, double Y ) const {
  return new hard(X, Y, DurMin + rand() % (DurMax - DurMin + 1));
}

} // End of 'bricks' namespace
} // End of 'ark' namespace
