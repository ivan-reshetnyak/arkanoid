#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <exception>

#include "GL/freeglut.h"
#include "engine.h"
#include "mod_adder.h"
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

  *Instance << new brick;

  int Cols, Rows;
  double YSpace, Td;
  std::ifstream File("settings/brick");
  File >> Rows >> Cols >> Td >> Td >> YSpace;

  double SX = 2. / Cols;
  for (int Row = 0; Row < Rows; Row++)
    for (int Col = 0; Col < Cols; Col++)
      Bricks.push_back((brick_p)createBrick(-1. + SX * (0.5 + Col), 1. - YSpace * (0.5 + Row)));

  Balls.push_back(ball_p(new ball(0., -0.5)));
  Mods.push_back(mod_p(new mods::death()));
  Mods.push_back(mod_p(new mods::bounds()));

  std::ifstream GameSet("settings/game");
  GameSet >> Lives;

  glutMainLoop();
}

void engine::update( void ) {
  Instance->Timer.update();
  std::cout << (int)(1. / Instance->Timer.getDeltaTime()) << "         \r";

  for (auto &Ball : Instance->Balls)
    Ball->update(*Instance);

  std::vector<brick_p> Dead;
  for (auto &Brick : Instance->Bricks) {
    Brick->update(*Instance);
    if (Brick->isDead())
      Dead.push_back(Brick);
  }
  for (auto &Brick : Dead)
    Instance->Bricks.erase(std::remove(Instance->Bricks.begin(), Instance->Bricks.end(), Brick), Instance->Bricks.end());

  std::vector<mod_p> DeadMods;
  for (auto &Mod : Instance->Mods) {
    Mod->update(*Instance);
    if (Mod->isDead())
      DeadMods.push_back(Mod);
  }
  for (auto &Mod : DeadMods)
    Instance->Mods.erase(std::remove(Instance->Mods.begin(), Instance->Mods.end(), Mod), Instance->Mods.end());
}

void engine::displayFunc( void ) {
  glClearColor(0, 0, 0, 1);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);;
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto &Mod : Instance->Mods)
    Mod->render(*Instance);
  Instance->Paddle.render(*Instance);
  for (auto &Brick : Instance->Bricks)
    Brick->render(*Instance);
  for (auto &Ball : Instance->Balls)
    Ball->render(*Instance);

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

brick * engine::createBrick( double X, double Y ) {
  int TotalWeight = 0;
  for (const auto &BrickRef : Instance->BrickPool)
    TotalWeight += BrickRef->getWeight();

  int Roll = (rand() % TotalWeight) + 1;

  for (const auto &BrickRef : Instance->BrickPool) {
    if (Roll <= BrickRef->getWeight())
      return BrickRef->create(X, Y);
    Roll -= BrickRef->getWeight();
  }

  /*
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
  Roll -= BRICK_HARD_WEIGHT;
  if (Roll <= BRICK_ADDER_WEIGHT)
    return new bricks::modded<mods::adder>(X, Y, BRICK_ADDER_COLOR);
  Roll -= BRICK_ADDER_WEIGHT;
  */

  return nullptr;
}

engine::engine( void ) {
}

engine::~engine( void ) {
  Balls.clear();
  Mods.clear();
  BrickPool.clear();
  Bricks.clear();
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

engine & engine::operator<<( mod_p NewMod ) {
  Mods.push_back(NewMod);
  return *this;
}

engine & engine::operator<<( brick *BrickRef ) {
  BrickPool.push_back((brick_p)BrickRef);
  return *this;
}

int engine::getLives( void ) const {
  return Lives;
}

void engine::damage( int Dmg ) {
  Lives -= Dmg;
}

} // End of 'ark' namespace
