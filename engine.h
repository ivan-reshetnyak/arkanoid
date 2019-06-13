#pragma once

#include <vector>
#include <memory>

#include "timer.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"
#include "modifier.h"

namespace ark {

class engine {
  using ball_p = std::shared_ptr<ball>;

public:
  static engine & getInstance( void );
  void init( int argc, char *argv[], int W, int H );
  int getW( void ) const;
  int getH( void ) const;
  timer & getTimer( void );
  std::vector<ball_p> & getBalls( void );
  paddle & getPaddle( void );
  engine & operator<<( modifier *NewMod );
  int getLives( void ) const;
  void damage( int Dmg );

private:
  static engine *Instance;
  timer Timer;
  paddle Paddle;
  int WinW, WinH, Lives;
  std::vector<ball_p> Balls;
  std::vector<brick *> Bricks;
  std::vector<modifier *> Mods;

  engine( void );
  static void displayFunc( void );
  static void keyboardFunc( unsigned char Key, int X, int Y );
  static void specialFunc( int Key, int X, int Y );
  static void reshapeFunc( int NewW, int NewH );
  static void mouseFunc( int Button, int State, int X, int Y );
  static void update( void );
  static brick * createBrick( double X, double Y );
  ~engine( void );
};

} // End of 'ark' namespace
