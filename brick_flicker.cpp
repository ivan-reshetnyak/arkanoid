#pragma once

#include <cstdlib>

#include <fstream>

#include "GL/freeglut.h"
#include "ball.h"
#include "engine.h"
#include "brick_flicker.h"

namespace ark {
namespace bricks {

int flicker::Weight;
double flicker::PerMin, flicker::PerMax, flicker::Alpha;

flicker::flicker( void ) {
  std::ifstream File("settings/brick_flicker");
  File >> Weight >> Color.R >> Color.G >> Color.B >> Alpha
       >> PerMin >> PerMax;
}

flicker::flicker( double X, double Y, double Period ) : brick(X, Y), Period(Period) {
  std::ifstream File("settings/brick_flicker");
  File >> Weight >> Color.R >> Color.G >> Color.B;

  StateTime = 0;
}

int flicker::getWeight( void ) const {
  return Weight;
}

brick * flicker::create( double X, double Y ) const {
  return new flicker(X, Y, PerMin + (double)rand() / RAND_MAX * (PerMax - PerMin));
}

void flicker::update( engine &Engine ) {
  StateTime += Engine.getTimer().getDeltaTime();
  while (StateTime >= Period) {
    StateTime -= Period;
    IsActive = !IsActive;
  }
  if (!IsActive)
    return;

  auto Balls = Engine.getBalls();
  for (const auto &Ball : Balls) {
    double
      BX = Ball->getX(), BY = Ball->getY(),
      BW2 = Ball->getW() * 0.5, BH2 = Ball->getH() * 0.5,
      HW = Width * 0.5, HH = Height * 0.5;
    if (((BX - BW2 >= X - HW && BX - BW2 <= X + HW) ||
         (BX + BW2 >= X - HW && BX + BW2 <= X + HW)) &&
        ((BY - BH2 >= Y - HH && BY - BH2 <= Y + HH) ||
         (BY + BH2 >= Y - HH && BY + BH2 <= Y + HH))) {
      if (BX < X - HW || BX > X + HW) {
        Ball->bounceVertical();
        Ball->update(Engine);
      }
      if (BY < Y - HH || BY > Y + HH) {
        Ball->bounceHorizontal();
        Ball->update(Engine);
      }

      onHit(Engine);
    }
  }
}

void flicker::render( engine &Engine ) const {
  //if (!IsActive)
  //  return;

  double
    HW = 0.5 * Width,
    HH = 0.5 * Height;
  glColor4d(Color.R, Color.G, Color.B, IsActive ? 1 : Alpha);
  glRectd(X - HW, Y - HH, X + HW, Y + HH);
}

} // End of 'bricks' namespace
} // End of 'ark' namespace
