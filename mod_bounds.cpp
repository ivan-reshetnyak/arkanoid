#pragma once

#include "mod_bounds.h"
#include "engine.h"
#include "ball.h"

namespace ark {
namespace mods {

void bounds::update( engine &Engine ) {
  for (auto &Ball : Engine.getBalls()) {
    if (Ball->getX() - 0.5 * Ball->getW() < -1) {
      Ball->setX(-1 + 0.5 * Ball->getW());
      Ball->bounceVertical();
    }

    if (Ball->getX() + 0.5 * Ball->getW() > 1) {
      Ball->setX(1 - 0.5 * Ball->getW());
      Ball->bounceVertical();
    }

    if (Ball->getY() + 0.5 * Ball->getH() > 1) {
      Ball->setY(1 - 0.5 * Ball->getH());
      Ball->bounceHorizontal();
    }
  }
}

bool bounds::isDead( void ) const {
  return false;
}

const char * bounds::settingsFileName( void ) const {
  return "settings/game";
}

} // End of 'mods' namespace
} // End of 'ark' namespace
