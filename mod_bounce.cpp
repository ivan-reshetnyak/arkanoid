#pragma once

#include <algorithm>

#include "GL/freeglut.h"
#include "mod_bounce.h"
#include "engine.h"
#include "paddle.h"

namespace ark {
namespace mods {

bounce::bounce( void ) {
  IsSpent = false;
  int W;
  std::ifstream File(settingsFileName());
  File >> W >> Color.R >> Color.G >> Color.B;
}

void bounce::update( engine &Engine ) {
  paddle &Paddle = Engine.getPaddle();

  std::vector<std::shared_ptr<ball>> Out;
  for (auto &Ball : Engine.getBalls()) {
    if (Ball->getY() - Ball->getH() * 0.5 < -1 + Paddle.getH() * 0.5)
      // Ball below paddle
      if (!(((Ball->getX() + Ball->getW() * 0.5 >= Paddle.getX() - Paddle.getW() * 0.5 &&
              Ball->getX() + Ball->getW() * 0.5 <= Paddle.getX() + Paddle.getW() * 0.5) || 
             (Ball->getX() - Ball->getW() * 0.5 >= Paddle.getX() - Paddle.getW() * 0.5 &&
              Ball->getX() - Ball->getW() * 0.5 <= Paddle.getX() + Paddle.getW() * 0.5)))) {
      // Ball miss paddle
      Ball->bounceHorizontal();
      Ball->bounceVertical();
      Ball->update(Engine);

      IsSpent = true;
    }
  }
}

bool bounce::isDead( void ) const {
  return IsSpent;
}

void bounce::render( engine &Engine ) const {
  if (IsSpent)
    return;

  paddle &Paddle = Engine.getPaddle();
  glColor3d(Color.R, Color.G, Color.B);
  glRectd(-1, -1 + Paddle.getH() * 0.45, 1, -1 + Paddle.getH() * 0.5);
}

const char * bounce::settingsFileName( void ) const {
  return "settings/brick_bounce";
}

} // End of 'mods' namespace
} // End of 'ark' namespace
