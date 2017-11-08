#include "hal.h"
#include "hal_interface.h"
#include "hal_dummy.h"
//#include <iostream>


HAL::HAL(QObject *parent) : QObject(parent)
{
  this->setHWType("");
}

HAL::~HAL()
{
  if (this->HAL_instance) {
    delete HAL_instance;
  }

  if (valueUpdater) {
      valueUpdater->stop();
      delete valueUpdater;
  }
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
      return HALErrors::AlreadyInitialized;
    }
  // Test for empty hwtype
  if (this->hwType.isEmpty()) {
      return HALErrors::HWTypeNotSet;
    }

  // Select class according to give hwtype
  if (QString::compare(this->hwType,
                       QString("hal_dummy"), Qt::CaseInsensitive) == 0) {
      this->HAL_instance = new hal_dummy();
      return HALErrors::NoError;
    }
  else {
    // We end up here if hwtype is incorrect
    return HALErrors::HWTypeNotRecognized;
  }

  // Finally if non of the cases match we return unknown error
  return HALErrors::UnknownError;
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

int HAL::startTimer(const double period)
{
  if (valueUpdater) {
      return HALErrors::TimerAlreadyRunning;
    }
  valueUpdater = new QTimer(this);
  connect(valueUpdater, SIGNAL(timeout()), this, SLOT(updateValues()));
  this->startTimer(period*1000);
  return HALErrors::NoError;
}

void HAL::stopTimer()
{
  if (valueUpdater) {
      valueUpdater->stop();
      delete valueUpdater;
      valueUpdater = nullptr;
  }
}
