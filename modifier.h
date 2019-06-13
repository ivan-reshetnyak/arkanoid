#pragma once

namespace ark {

class engine;

class modifier {
public:
  modifier( void ) = default;
  virtual void update( engine &Engine ) = 0;
  virtual bool isDead( void ) const = 0;
  virtual void render( void ) const {
  }
};

} // End of 'ark' namespace
