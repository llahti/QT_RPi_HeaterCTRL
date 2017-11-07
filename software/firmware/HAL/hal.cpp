#include "hal.h"
#include "hal_interface.h"
#include "hal_dummy.h"
//#include <iostream>


HAL::HAL(QObject *parent)
{
  this->setParent(parent);
  this->setHWType("");
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

void HAL::updateValues()
{
  if (HAL_instance) {
    // Variables for data
    double boilerTemp;
    double extGasTemp;
    bool circulationPump;
    double ExtFan;

    // Measure
    HAL_interface* h = HAL_instance;  // h for short
    h->measureBoilerTemp(boilerTemp);
    h->measureExtGasTemp(extGasTemp);
    h->getCirculationPump(circulationPump);
    h->getExtFanSpeed(ExtFan);

    // Emit signals
    emit measuredBoilerTemp(boilerTemp);
    emit measuredExtGasTemp(extGasTemp);
    emit changedCirculationPumpState(circulationPump);
    emit changedExtFanSpeed(ExtFan);
  }
}


void HAL::setCirculationPump(bool state)
{
  if (HAL_instance){
    HAL_instance->setCirculationPump(state);
    emit changedCirculationPumpState(state);
  }
}


void HAL::setExtFanSpeed(double value)
{
  if (HAL_instance) {
    HAL_instance->setExtFanSpeed(value);
    emit changedExtFanSpeed(value);
  }
}
