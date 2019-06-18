#pragma once

#include <cstdlib>

#include "mod_speed.h"
#include "engine.h"
#include "ball.h"

namespace ark {
namespace mods {

speed::speed( void ) {
  Changed = false;
  std::ifstream File(settingsFileName());
  int Ti;
  double Td;
  File >> Ti >> Td >> Td >> Td;
  double MulMin, MulMax;
  File >> MulMin >> MulMax;
  Mul = MulMin + (double)rand() / RAND_MAX * (MulMax - MulMin);
}

void speed::update( engine &Engine ) {
  auto &Balls = Engine.getBalls();
  for (auto &Ball : Balls)
    Ball->modSpeed(Mul);
  Changed = true;
}

bool speed::isDead( void ) const {
  return Changed;
}

const char * speed::settingsFileName( void ) const {
  return "settings/brick_speed";
}

} // End of 'mods' namespace
} // End of 'ark' namespace
