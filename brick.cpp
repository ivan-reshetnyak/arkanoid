#pragma once

#include <fstream>

#include "GL/freeglut.h"
#include "ball.h"
#include "engine.h"
#include "brick.h"

namespace ark {

int brick::Weight = 0;
double brick::Width, brick::Height;

brick::brick( void ) : X(X), Y(Y) {
  std::ifstream File("settings/brick_standart");
  File >> Weight >> Color.R >> Color.G >> Color.B;

  int R, C;
  std::ifstream General("settings/brick");
  General >> R >> C >> Width >> Height;
}

brick::brick( double X, double Y ) : X(X), Y(Y) {
  std::ifstream File("settings/brick_standart");
  File >> Weight >> Color.R >> Color.G >> Color.B;

  Durability = 1;
}

void brick::update( engine &Engine ) {
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

bool brick::isDead( void ) const {
  return Durability <= 0;
}

void brick::render( engine &Engine ) const {
  double
    HW = 0.5 * Width,
    HH = 0.5 * Height;
  glColor3d(Color.R, Color.G, Color.B);
  glRectd(X - HW, Y - HH, X + HW, Y + HH);
}

void brick::onHit( engine &Engine ) {
  Durability--;
}

int brick::getWeight( void ) const {
  return Weight;
}

brick * brick::create( double X, double Y ) const {
  return new brick(X, Y);
}

} // End of 'ark' namespace
