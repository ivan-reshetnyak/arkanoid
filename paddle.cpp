#include <fstream>

#include "GL/freeglut.h"
#include "paddle.h"

namespace ark {

void paddle::move( direction Dir, const timer &Timer ) {
  double DirMul = (Dir == direction::LEFT) ? -1 : 1;
  X += Timer.getDeltaTime() * DirMul * Speed;
  fit();
}

void paddle::modSpeed( double Mul ) {
  Speed *= Mul;
}

void paddle::resize( double Mul ) {
  TargetWidth *= Mul;
  ResizeSpeed = (TargetWidth - Width) / ResizeTime;
}

void paddle::update( const timer &Timer ) {
  if (ResizeSpeed != 0) {
    // Resizing
    double NewWidth = Width + ResizeSpeed * Timer.getDeltaTime();

    if (abs(Width - TargetWidth) < abs(NewWidth - TargetWidth))
      Width = TargetWidth;
    else
      Width = NewWidth;
  }
  fit();
}

void paddle::fit( void ) {
  if (X - 0.5 * Width < -1)
    X = -1 + 0.5 * Width;

  if (X + 0.5 * Width > 1)
    X = 1 - 0.5 * Width;
}

paddle::paddle( void ) {
  X = 0;
  Y = -1;

  std::ifstream File("settings/paddle");
  File >> Speed >> Width >> Height
       >> ResizeTime
       >> Color.R >> Color.G >> Color.B;
  ResizeSpeed = 0;
  TargetWidth = Width;
}

void paddle::render( engine &Engine ) const {
  double
    HW = 0.5 * Width,
    HH = 0.5 * Height;
  glColor3d(Color.R, Color.G, Color.B);
  glRectd(X - HW, Y - HH, X + HW, Y + HH);
}

double paddle::getX( void ) const {
  return X;
}

double paddle::getW( void ) const {
  return Width;
}

double paddle::getH( void ) const {
  return Height;
}

} // End of 'ark' namespace
