#pragma once

#include "constants.h"
#include "modifier.h"

namespace ark {

class engine;

namespace mods {

class bounce : public modifier {
public:
  bounce( void );
  virtual void update( engine &Engine ) override;
  virtual bool isDead( void ) const override;
  virtual void render( engine &Engine ) const override;
  virtual const char * settingsFileName( void ) const final;
private:
  bool IsSpent;
};

} // End of 'mods' namespace
} // End of 'ark' namespace
