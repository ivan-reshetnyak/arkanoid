#pragma once

#include "constants.h"
#include "modifier.h"

namespace ark {

class engine;

namespace mods {

class death : public modifier {
public:
  death( void );
  virtual void update( engine &Engine ) override;
  virtual bool isDead( void ) const final;

private:
  int Lives;
};

} // End of 'mods' namespace
} // End of 'ark' namespace
