#include "hal_dummy.h"
#include "hal_interface.h"
#include <QDebug>

int hal_dummy::measureBoilerTemp(double& result)
{
  result = boilerTemp;
  return 0;
}

int hal_dummy::measureExtGasTemp(double& result)
{
  result = extGasTemp;
  return 0;
}

int hal_dummy::getCirculationPump(bool &state)
{
  state = circulationPump;
  return 0;
}

int hal_dummy::getExtFanSpeed(double& result)
{
  result = extFanSpeed;
  return 0;
}

int hal_dummy::setCirculationPump(bool state)
{
  circulationPump = state;
  return 0;
}

int hal_dummy::setExtFanSpeed(double speed)
{
  extFanSpeed = speed;  // Prevent warning, remove this line when method is implemented
  return 0;
}
