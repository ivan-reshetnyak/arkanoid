#pragma once

#include "constants.h"
#include "modifier.h"

namespace ark {

class engine;

namespace mods {

class adder : public modifier {
public:
  adder( int ToAdd );
  virtual void update( engine &Engine ) override;
  virtual bool isDead( void ) const final;

private:
  double Time;
  int ToAdd, Added;
};

} // End of 'mods' namespace
} // End of 'ark' namespace
