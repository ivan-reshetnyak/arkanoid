#pragma once

#include "modifier.h"

namespace ark {

class engine;

namespace mods {

class heal : public modifier {
public:
  heal( void );
  virtual void update( engine &Engine ) override;
  virtual bool isDead( void ) const final;
  virtual const char * settingsFileName( void ) const final;
private:
  bool Healed;
};

} // End of 'mods' namespace
} // End of 'ark' namespace
