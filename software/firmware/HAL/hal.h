#ifndef HAL_H
#define HAL_H

#include "hal_global.h"
#include "hal_interface.h"
#include <QString>
#include <string>
#include <QMutex>


class HALSHARED_EXPORT HAL
{
public:
  HAL();
  HAL(QString hwtype);
  int init();
  int measureBoilerTemp(double& result);
  int measureExtGasTemp(double& result);
  QString getHWType();
  int setExtFanSpeed(const double speed);
  int setHWType(QString hwtype);

private:
  // Store pointer to device specific HAL
  HAL_interface* HAL_instance = nullptr;
  // Keep information of hardware type
  QString hwType;
};

#endif // HAL_H
