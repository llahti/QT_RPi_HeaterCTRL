#include "heaterstatus.h"

HeaterStatus::HeaterStatus()
{
  // Initialize status to safe values
  this->BoilerTemp = 0.;
  this->ExhaustGasTemp = 0.;
  this->ExtFanSpeedSetting= 0.;
  this->ExtFanSpeedMeasured = 0.;
  this->CirculationPumpState = false;
}
