#pragma once

#include "modifier.h"

namespace ark {

class engine;

namespace mods {

class adder : public modifier {
public:
  adder( void );
  virtual void update( engine &Engine ) override;
  virtual bool isDead( void ) const final;
  virtual const char * settingsFileName( void ) const final;

private:
  double Time, Period;
  int ToAdd, Added;
};

} // End of 'mods' namespace
} // End of 'ark' namespace
