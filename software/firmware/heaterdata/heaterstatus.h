#ifndef HEATERSTATUS_H
#define HEATERSTATUS_H


class HeaterStatus
{
public:
  HeaterStatus();

private:
  double BoilerTemp;  // Water temperature in boiler
  double ExhaustGasTemp;  // Exhaust gas temperature
  double ExtFanSpeedSetting;  // Set point for ext.fan speed 0..100%
  double ExtFanSpeedMeasured;  // Measured ext.fan speed
  bool CirculationPumpState;  // status flag for boiler circulation pump
};

#endif // HEATERSTATUS_H
