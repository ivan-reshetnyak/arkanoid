#pragma once

#include <fstream>

namespace ark {

class engine;

class modifier {
public:
  modifier( void ) = default;
  virtual void update( engine &Engine ) = 0;
  virtual bool isDead( void ) const = 0;
  virtual void render( engine &Engine ) const {
  }
  virtual const char * settingsFileName( void ) const = 0;
};

} // End of 'ark' namespace
