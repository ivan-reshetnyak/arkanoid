#pragma once

#include <algorithm>

#include "mod_adder.h"
#include "engine.h"
#include "paddle.h"

namespace ark {
namespace mods {

adder::adder( void ) : Added(0) {
  int Ti;
  double Td;
  std::ifstream File(settingsFileName());
  File >> Ti >> Td >> Td >> Td;

  File >> ToAdd >> Period;

  Time = 0;
}

void adder::update( engine &Engine ) {
  Time += Engine.getTimer().getDeltaTime();
  if (Time >= Period) {
    Time -= Period;
    Engine.getBalls().push_back(std::shared_ptr<ball>(new ball(0, -0.5)));
    Added++;
  }
}

bool adder::isDead( void ) const {
  return Added >= ToAdd;
}

const char * adder::settingsFileName( void ) const {
  return "settings/brick_adder";
}

} // End of 'mods' namespace
} // End of 'ark' namespace
