#ifndef HAL_DUMMY_H
#define HAL_DUMMY_H

#include "hal_interface.h"

class hal_dummy : public HAL_interface
{
public:
  hal_dummy();
  int measureBoilerTemp(double& result) override;
  int measureExtGasTemp(double& result) override;
  int getExtFanSpeed(double& result) override;
  int setExtFanSpeed(double speed) override;

private:
  double extFanSpeed;
};

#endif // HAL_DUMMY_H
