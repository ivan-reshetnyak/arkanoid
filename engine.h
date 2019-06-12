#pragma once

#include <vector>

#include "timer.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"

namespace ark {

class engine {
public:
  static engine & getInstance( void );
  void init( int argc, char *argv[], int W, int H );
  int getW( void ) const;
  int getH( void ) const;
  const timer & getTimer( void ) const;
  std::vector<ball *> & getBalls( void ) ;

private:
  static engine *Instance;
  timer Timer;
  paddle Paddle;
  int WinW, WinH;
  std::vector<ball *> Balls;
  std::vector<brick *> Bricks;

  engine( void );
  static void displayFunc( void );
  static void keyboardFunc( unsigned char Key, int X, int Y );
  static void specialFunc( int Key, int X, int Y );
  static void reshapeFunc( int NewW, int NewH );
  static void mouseFunc( int Button, int State, int X, int Y );
  static void update( void );
  ~engine( void );
};

} // End of 'ark' namespace
