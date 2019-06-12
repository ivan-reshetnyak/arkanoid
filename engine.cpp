#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <exception>

#include "GL/freeglut.h"
#include "engine.h"
#include "constants.h"

namespace ark {

engine *engine::Instance = nullptr;

engine & engine::getInstance( void ) {
  if (Instance == nullptr)
    Instance = new engine;

  return *engine::Instance;
}

void engine::init( int argc, char *argv[], int W, int H ) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

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
}

void engine::displayFunc( void ) {
  glClearColor(0, 0, 0, 1);
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

engine::engine( void ) : Paddle({PADDLE_R, PADDLE_G, PADDLE_B}) {
  Balls.push_back(new ball({BALL_R, BALL_G, BALL_B}));

  for (int i = 0; i < 15; i++) {
    double
      RX = ((double)rand() / RAND_MAX) * 2 - 1,
      RY = ((double)rand() / RAND_MAX) * 2 - 1;
    Bricks.push_back(new brick(RX, RY));
  }
}

engine::~engine( void ) {
  for (auto &Ball : Balls)
    delete Ball;
  Balls.clear();

  for (auto &Brick : Bricks)
    delete Brick;
  Bricks.clear();
}

int engine::getW( void ) const {
  return WinW;
}

int engine::getH( void ) const {
  return WinH;
}

const timer & engine::getTimer( void ) const {
  return Timer;
}

std::vector<ball *> & engine::getBalls( void ) {
  return Balls;
}

} // End of 'ark' namespace
