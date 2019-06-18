#pragma once

#include <memory>

#include "ball.h"
#include "modifier.h"

namespace ark {

class engine;

namespace mods {

class speed : public modifier {
public:
  speed( void );
  virtual void update( engine &Engine ) override;
  virtual bool isDead( void ) const final;
  virtual const char * settingsFileName( void ) const final;
private:
  bool Changed;
  double Mul;
};

} // End of 'mods' namespace
} // End of 'ark' namespace
