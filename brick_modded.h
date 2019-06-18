#pragma once

#include <memory>

#include "color.h"

namespace ark {

class engine;

namespace bricks {

template<class mod_t>
class modded : public brick {
public:
  modded( void ) : ModPtr(new mod_t) {
    std::ifstream File(ModPtr->settingsFileName());
    File >> Weight >> Color.R >> Color.G >> Color.B;
  }

  virtual int getWeight( void ) const final {
    return Weight;
  }

  virtual brick * create( double X, double Y ) const final {
    return new modded(X, Y);
  }

protected:
  modded( double X, double Y ) : brick(X, Y), ModPtr(new mod_t) {
    std::ifstream File(ModPtr->settingsFileName());
    File >> Weight >> Color.R >> Color.G >> Color.B;
  }

  std::shared_ptr<mod_t> ModPtr;
  virtual void onHit( engine &Engine ) {
    Durability--;
    Engine << ModPtr;
  }
private:
  int Weight;
};

} // End of 'bricks' namespace
} // End of 'ark' namespace
