#pragma once

#include <algorithm>

#include "mod_heal.h"
#include "engine.h"
#include "paddle.h"

namespace ark {
namespace mods {

heal::heal( void ) {
  Healed = false;
}

void heal::update( engine &Engine ) {
  Engine.damage(-1);
  Healed = true;
}

bool heal::isDead( void ) const {
  return Healed;
}

const char * heal::settingsFileName( void ) const {
  return "settings/brick_heal";
}

} // End of 'mods' namespace
} // End of 'ark' namespace
