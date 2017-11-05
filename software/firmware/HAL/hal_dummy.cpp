#include "hal_dummy.h"
#include "hal_interface.h"

hal_dummy::hal_dummy()
{
  extFanSpeed = 0.0;
}

int hal_dummy::measureBoilerTemp(double& result)
{
  result = 80.5;
  return 0;
}

int hal_dummy::measureExtGasTemp(double& result)
{
  result = 199.6;
  return 0;
}

int hal_dummy::getExtFanSpeed(double& result)
{
  result = extFanSpeed;
  return 0;
}

int hal_dummy::setExtFanSpeed(double speed)
{
  extFanSpeed = speed;  // Prevent warning, remove this line when method is implemented
  return 0;
}
