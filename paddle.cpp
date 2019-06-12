#include "GL/freeglut.h"
#include "paddle.h"
#include "constants.h"

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

paddle::paddle( const color &Col ) : Color(Col) {
  X = 0;
  Y = -1;
  Speed = PADDLE_SPEED;
  Width = TargetWidth = PADDLE_WIDTH;
  Height = PADDLE_HEIGHT;
  ResizeTime = PADDLE_RESIZE_TIME;
  ResizeSpeed = 0;
}

void paddle::render( void ) const {
  double
    HW = 0.5 * Width,
    HH = 0.5 * Height;
  glColor3d(Color.R, Color.G, Color.B);
  glRectd(X - HW, Y - HH, X + HW, Y + HH);
}

} // End of 'ark' namespace
