#pragma once

#include "engine.h"
#include "brick_adder.h"
#include "constants.h"
#include "mod_adder.h"

namespace ark {
namespace bricks {

adder::adder( double X, double Y, int ToAdd ) : brick(X, Y), ToAdd(ToAdd) {
  Color = BRICK_ADDER_COLOR;
}

void adder::onHit( engine &Engine ) {
  Durability--;
  Engine << new mods::adder(ToAdd);
}

} // End of 'bricks' namespace
} // End of 'ark' namespace
