#include "hal.h"
#include "hal_interface.h"
#include "hal_dummy.h"
#include <iostream>


HAL::HAL()
{
  this->setHWType("");
}

HAL::HAL(QString hwtype)
{
  this->setHWType(hwtype);
}

/**
 * @brief HAL::init
 * @return 0 when successful
 *         1 when HAL is already initialized
 *         2 when hw-type is not given
 *         3 when hw-type is not recognized
 *         4 unknown error
 *         5 HAL is not initialized
 */
int HAL::init()
{
  // When hal instance is already initialized we don't want to do it again
  if (this->HAL_instance) {
      return 1;
    }
  // Test for empty hwtype
  if (this->hwType.isEmpty()) {
      return 2;
    }

  // Select class according to give hwtype
  if (QString::compare(this->hwType,
                       QString("hal_dummy"), Qt::CaseInsensitive) == 0) {
      this->HAL_instance = new hal_dummy();
      return 0;
    }
  else {
    // We end up here if hwtype is incorrect
    return 3;
  }

  // Finally if non of the cases match we return unknown error
  return 4;
}

QString HAL::getHWType()
{
  QString hwtype = QString(this->hwType);
  return hwtype;
}

int HAL::measureBoilerTemp(double& result)
{
  if (HAL_instance) {
    int ret = this->HAL_instance->measureBoilerTemp(result);
    return ret;
    }
  else {
    return 5;
    }
}

int HAL::measureExtGasTemp(double& result)
{
  if (HAL_instance) {
    return this->HAL_instance->measureExtGasTemp(result);
    }
  else {
      return 5;
    }
}

int HAL::setHWType(QString hwtype)
{
  if (HAL_instance) {
      // After running Init we shouldn't be able to set hwtype
      return 1;
    }
  else {
    this->hwType = QString(hwtype);
    return 0;
  }
}

int HAL::setExtFanSpeed(const double speed)
{
  if (HAL_instance) {
      return this->HAL_instance->setExtFanSpeed(speed);
    }
  else {
      return 5;
    }
}
