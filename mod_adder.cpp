#pragma once

#include <algorithm>

#include "constants.h"
#include "mod_adder.h"
#include "engine.h"
#include "paddle.h"

namespace ark {
namespace mods {

adder::adder( void ) : ToAdd(ADDER_TO_ADD), Added(0) {
  Time = 0;
}

void adder::update( engine &Engine ) {
  Time += Engine.getTimer().getDeltaTime();
  if (Time >= ADDER_PERIOD) {
    Time -= ADDER_PERIOD;
    Engine.getBalls().push_back(std::shared_ptr<ball>(new ball(BALL_COLOR, 0, -0.5)));
    Added++;
  }
}

bool adder::isDead( void ) const {
  return Added >= ToAdd;
}

} // End of 'mods' namespace
} // End of 'ark' namespace
