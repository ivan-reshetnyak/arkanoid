#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <exception>

#include "GL/freeglut.h"
#include "engine.h"
#include "constants.h"
#include "brick_flicker.h"
#include "brick_hard.h"
#include "mod_death.h"
#include "mod_bounds.h"

namespace ark {

engine *engine::Instance = nullptr;

engine & engine::getInstance( void ) {
  if (Instance == nullptr)
    Instance = new engine;

  return *engine::Instance;
}

void engine::init( int argc, char *argv[], int W, int H ) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

  glutInitWindowSize(W, H);
  glutInitWindowPosition(0, 0);

  glutCreateWindow("Arkanoid");

  glutKeyboardFunc(keyboardFunc);
  glutMouseFunc(mouseFunc);
  glutSpecialFunc(specialFunc);
  glutDisplayFunc(displayFunc);
  glutReshapeFunc(reshapeFunc);
  glutIdleFunc(update);
  //glutMotionFunc(MouseMotion);
  //glutMouseWheelFunc(MouseWheel);

  Balls.push_back(ball_p(new ball({BALL_R, BALL_G, BALL_B}, 0., -0.5)));
  Mods.push_back(new mods::death());
  Mods.push_back(new mods::bounds());

  glutMainLoop();
}

void engine::update( void ) {
  Instance->Timer.update();
  std::cout << (int)(1. / Instance->Timer.getDeltaTime()) << "         \r";

  for (auto &Ball : Instance->Balls)
    Ball->update(*Instance);

  std::vector<brick *> Dead;
  for (auto &Brick : Instance->Bricks) {
    Brick->update(*Instance);
    if (Brick->isDead())
      Dead.push_back(Brick);
  }
  for (auto &Brick : Dead) {
    Instance->Bricks.erase(std::remove(Instance->Bricks.begin(), Instance->Bricks.end(), Brick), Instance->Bricks.end());
    delete Brick;
  }

  std::vector<modifier *> DeadMods;
  for (auto &Mod : Instance->Mods) {
    Mod->update(*Instance);
    if (Mod->isDead())
      DeadMods.push_back(Mod);
  }
  for (auto &Mod : DeadMods) {
    Instance->Mods.erase(std::remove(Instance->Mods.begin(), Instance->Mods.end(), Mod), Instance->Mods.end());
    delete Mod;
  }
}

void engine::displayFunc( void ) {
  glClearColor(0, 0, 0, 1);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);;
  glClear(GL_COLOR_BUFFER_BIT);

  Instance->Paddle.render();
  for (auto &Brick : Instance->Bricks)
    Brick->render();;
  for (auto &Ball : Instance->Balls)
    Ball->render();;

  glFlush();
  glutSwapBuffers();
  glutPostRedisplay();
}

void engine::keyboardFunc( unsigned char Key, int X, int Y ) {
  switch (Key) {
  case 'P':
  case 'p':
    Instance->Timer.pauseToggle();
    break;
  case 27:
    delete Instance;
    Instance = nullptr;
    exit(0);
  }
}

void engine::specialFunc( int Key, int X, int Y ) {
  switch (Key) {
  case GLUT_KEY_RIGHT:
    // Move right
    Instance->Paddle.move(paddle::direction::RIGHT, Instance->Timer);
    break;
  case GLUT_KEY_LEFT:
    // Move left
    Instance->Paddle.move(paddle::direction::LEFT, Instance->Timer);
    break;
  }
}

void engine::reshapeFunc( int NewW, int NewH ) {
  glViewport(0, 0, NewW, NewH);
  Instance->WinW = NewW;
  Instance->WinH = NewH;
}

void engine::mouseFunc( int Button, int State, int X, int Y ) {
}

static brick * createBrick( double X, double Y ) {
  static const int TotalWeight = BRICK_STANDART_WEIGHT + BRICK_FLICKER_WEIGHT + BRICK_HARD_WEIGHT;
  int Roll = (rand() % TotalWeight) + 1;

  if (Roll <= BRICK_STANDART_WEIGHT)
    return new brick(X, Y);
  Roll -= BRICK_STANDART_WEIGHT;
  if (Roll <= BRICK_FLICKER_WEIGHT) {
    double Period = BRICK_FLICKER_PERIOD_MIN + (double)rand() / RAND_MAX * (BRICK_FLICKER_PERIOD_MAX - BRICK_FLICKER_PERIOD_MIN);
    return new bricks::flicker(X, Y, Period);
  }
  Roll -= BRICK_FLICKER_WEIGHT;
  if (Roll <= BRICK_HARD_WEIGHT) {
    int Durab = BRICK_HARD_HP_MIN + rand() % (BRICK_HARD_HP_MAX - BRICK_HARD_HP_MIN);
    return new bricks::hard(X, Y, Durab);
  }
  Roll -= BRICK_FLICKER_WEIGHT;

  return new brick(X, Y);
}

engine::engine( void ) : Paddle({PADDLE_R, PADDLE_G, PADDLE_B}) {
  double SX = 2. / BRICK_COLUMNS;
  for (int Row = 0; Row < BRICK_ROWS; Row++)
    for (int Col = 0; Col < BRICK_COLUMNS; Col++)
      Bricks.push_back(createBrick(-1. + SX * (0.5 + Col), 1. - BRICK_YSPACING * (0.5 + Row)));
}

engine::~engine( void ) {
  Balls.clear();

  for (auto &Brick : Bricks)
    delete Brick;
  Bricks.clear();

  for (auto &Mod : Mods)
    delete Mod;
  Mods.clear();
}

int engine::getW( void ) const {
  return WinW;
}

int engine::getH( void ) const {
  return WinH;
}

timer & engine::getTimer( void ) {
  return Timer;
}

std::vector<engine::ball_p> & engine::getBalls( void ) {
  return Balls;
}

paddle & engine::getPaddle( void ) {
  return Paddle;
}

} // End of 'ark' namespace
