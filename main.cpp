#include <conio.h>

#include "memhooks.h"
#include "engine.h"

using namespace ark;

int main( int argc, char *argv[] ) {
  engine &Game = engine::getInstance();

  Game.init(argc, argv, 1366, 768);

  return 0;
}
