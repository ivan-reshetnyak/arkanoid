#include "GL/freeglut.h"
#include "engine.h"
#include "ball.h"
#include "constants.h"

namespace ark {

void ball::modSpeed( double Mul ) {
  XSpeed *= Mul;
  YSpeed *= Mul;
}

void ball::resize( double Mul ) {
  Width *= Mul;
  Height *= Mul;
}

void ball::update( engine &Engine ) {
  double Ratio = (double)Engine.getH() / Engine.getW();
  X += XSpeed * Engine.getTimer().getDeltaTime();
  Y += YSpeed * Engine.getTimer().getDeltaTime() / Ratio;
  Height = Width / Ratio;
}

ball::ball( const color &Col, double X, double Y ) : Color(Col), X(X), Y(Y) {
  XSpeed = YSpeed = BALL_SPEED;
  Width = BALL_XSIZE;
  Height = Width;
}

void ball::render( void ) const {
  double
    HW = 0.5 * Width,
    HH = 0.5 * Height;

  glColor3d(Color.R, Color.G, Color.B);
  glBegin(GL_POLYGON);
  for (int i = 0; i < BALL_DETAIL; i++) {
    double Phi = -(2 * 3.1415 / BALL_DETAIL) * i;
    glVertex2d(X + HW * cos(Phi), Y + HH * sin(Phi));
  }
  glEnd();
}

double ball::getX( void ) const {
  return X;
}

double ball::getY( void ) const {
  return Y;
}

double ball::getW( void ) const {
  return Width;
}

double ball::getH( void ) const {
  return Height;
}

void ball::bounceVertical( void ) {
  XSpeed *= -1;
}

void ball::bounceHorizontal( void ) {
  YSpeed *= -1;
}

void ball::bounce( double XProp, double YProp ) {
  double
    Sq = XSpeed * XSpeed + YSpeed * YSpeed,
    XS = sqrt(Sq / (1 + (YProp * YProp / XProp / XProp))),
    YS = XS * YProp / XProp;

  XSpeed = XSpeed / abs(XSpeed) * XS;
  YSpeed = YSpeed / abs(YSpeed) * YS;
}

void ball::setX( double NewX ) {
  X = NewX;
}

void ball::setY( double NewY ) {
  Y = NewY;
}

} // End of 'ark' namespace
