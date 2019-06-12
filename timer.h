#pragma once

#include <chrono>

namespace ark {

class timer {
public:
  timer( void );
  void update( void );
  void pause( void );
  void unpause( void );
  void pauseToggle( void );
  double getGlobalTime( void ) const;
  double getGlobalDeltaTime( void ) const;
  double getTime( void ) const;
  double getDeltaTime( void ) const;
  void setSpeed( double Mod );

private:
  using clock = std::chrono::steady_clock;
  double
    StartTime,
    GlobalTime, GlobalTimePrev, GlobalDeltaTime,  // Continuous time sinse birth
    Time, TimePrev, DeltaTime,                    // "In-game" time
    SpeedModifier;                                // "In-game" time speed mod
  bool Paused;

  // Get current time
  static double now( void );
};

} // End of 'ark' namespace
