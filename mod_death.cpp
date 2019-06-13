#pragma once

#include <algorithm>

#include "constants.h"
#include "mod_death.h"
#include "engine.h"
#include "paddle.h"

namespace ark {
namespace mods {

death::death( void ) {
  Lives = LIVES;
}

void death::update( engine &Engine ) {
  if (Lives <= 0)
    Engine.getTimer().pause();

  paddle &Paddle = Engine.getPaddle();

  std::vector<std::shared_ptr<ball>> Out;
  for (auto &Ball : Engine.getBalls()) {
    if (Ball->getY() - Ball->getH() * 0.5 < -1 + Paddle.getH() * 0.5 &&
        ((Ball->getX() + Ball->getW() * 0.5 >= Paddle.getX() - Paddle.getW() * 0.5 &&
          Ball->getX() + Ball->getW() * 0.5 <= Paddle.getX() + Paddle.getW() * 0.5) || 
         (Ball->getX() - Ball->getW() * 0.5 >= Paddle.getX() - Paddle.getW() * 0.5 &&
          Ball->getX() - Ball->getW() * 0.5 <= Paddle.getX() + Paddle.getW() * 0.5))) {
      // Ball hit paddle
      Ball->bounceHorizontal();
      Ball->update(Engine);
    } else if (Ball->getY() + Ball->getH() * 0.5 < -1) {
      // Ball miss paddle
      Ball->bounceHorizontal();
      Ball->bounceVertical();
      Ball->update(Engine);

      if (Engine.getBalls().size() - Out.size() <= 1)
        Lives--;
      else
        Out.push_back(Ball);
    }
  }
  for (auto &Ball : Out)
    Engine.getBalls().erase(std::remove(Engine.getBalls().begin(), Engine.getBalls().end(), Ball), Engine.getBalls().end());
}

bool death::isDead( void ) const {
  return false;
}

} // End of 'mods' namespace
} // End of 'ark' namespace
