#pragma once

#include "modifier.h"

namespace ark {

class engine;

namespace mods {

class bounds : public modifier {
public:
  bounds( void ) = default;
  virtual void update( engine &Engine ) override;
  virtual bool isDead( void ) const final;
  virtual const char * settingsFileName( void ) const final;
};

} // End of 'mods' namespace
} // End of 'ark' namespace
