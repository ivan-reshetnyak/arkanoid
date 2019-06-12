#pragma once

#include <chrono>

#include "timer.h"

namespace ark {

timer::timer( void ) {
  Paused = false;
  StartTime = now();
  GlobalTime = GlobalTimePrev = Time = TimePrev = 0;
  SpeedModifier = 1;
}

void timer::update( void ) {
  GlobalTimePrev = GlobalTime;
  GlobalTime = now() - StartTime;
  GlobalDeltaTime = GlobalTime - GlobalTimePrev;
  TimePrev = Time;
  if (!Paused)
    Time = Time + GlobalDeltaTime * SpeedModifier;
  DeltaTime = Time - TimePrev;
}

// Get current time
double timer::now( void ) {
  return std::chrono::duration_cast<std::chrono::microseconds>(clock::now().time_since_epoch()).count() * 0.000001;
}

void timer::pause( void ) {
  Paused = true;
}

void timer::unpause( void ) {
  Paused = false;
}

void timer::pauseToggle( void ) {
  Paused = !Paused;
}

double timer::getGlobalTime( void ) const {
  return GlobalTime;
}

double timer::getGlobalDeltaTime( void ) const {
  return GlobalDeltaTime;
}

double timer::getTime( void ) const {
  return Time;
}

double timer::getDeltaTime( void ) const {
  return DeltaTime;
}

void timer::setSpeed( double Mod ) {
  SpeedModifier = Mod;
}

} // End of 'ark' namespace
