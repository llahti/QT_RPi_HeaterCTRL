#ifndef HAL_INTERFACE_H
#define HAL_INTERFACE_H


class HAL_interface
{
public:
  HAL_interface() {}
  virtual int measureBoilerTemp(double& result) = 0;
  virtual int measureExtGasTemp(double& result) = 0;
  virtual int getCirculationPump(bool& state) = 0;
  virtual int getExtFanSpeed(double& result) = 0;
  virtual int setCirculationPump(bool state) = 0;
  virtual int setExtFanSpeed(const double speed) = 0;
};

#endif // HAL_INTERFACE_H
