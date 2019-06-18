#include <conio.h>

#include "memhooks.h"
#include "engine.h"
#include "brick.h"
#include "brick_hard.h"
#include "brick_flicker.h"
#include "brick_modded.h"
#include "mod_adder.h"
#include "mod_bounce.h"

using namespace ark;

int main( int argc, char *argv[] ) {
  engine &Game = engine::getInstance();

  Game << new bricks::hard << new bricks::flicker
       << new bricks::modded<mods::adder>
       << new bricks::modded<mods::bounce>;
  Game.init(argc, argv, 1366, 768);

  return 0;
}
