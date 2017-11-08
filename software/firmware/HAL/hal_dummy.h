#ifndef HAL_DUMMY_H
#define HAL_DUMMY_H

#include "hal_interface.h"

class hal_dummy : public HAL_interface
{
public:
  hal_dummy() {}
  ~hal_dummy() {}
  int measureBoilerTemp(double& result) override;
  int measureExtGasTemp(double& result) override;
  int getCirculationPump(bool& state) override;
  int getExtFanSpeed(double& result) override;
  int setCirculationPump(bool state) override;
  int setExtFanSpeed(double speed) override;

private:
  // Don't change these defaults, those are used in unit tests
  double boilerTemp = 80.5;
  bool circulationPump = true;
  double extFanSpeed = 41.5;
  double extGasTemp = 199.6;

};

#endif // HAL_DUMMY_H
