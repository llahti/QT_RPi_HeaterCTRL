#include <QDebug>

#include "hal.h"
#include "hal_interface.h"
#include "hal_dummy.h"


HAL::HAL(QObject *parent) : QObject(parent)
{
  this->setHWType("");
}

HAL::~HAL()
{
  if (this->HAL_instance) {
    delete HAL_instance;
  }

//  if (this->isRunning()) {
//      this->requestInterruption();
//      this->exit(0);
//  }
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
    MeasurementPackage circulationPump;
    HAL_instance->setCirculationPump(state);
    circulationPump.timestamp_ = QDateTime::currentDateTime();
    circulationPump.raw_measurements_.append(state);
    emit changedCirculationPumpState(circulationPump);
  }
}


void HAL::setExtFanSpeed(double value)
{
  if (HAL_instance) {
    MeasurementPackage ExtFan;
    HAL_instance->setExtFanSpeed(value);
    ExtFan.timestamp_ = QDateTime::currentDateTime();
    ExtFan.raw_measurements_.append(value);
    emit changedExtFanSpeed(ExtFan);
  }
}


void HAL::updateValues()
{
  if (HAL_instance) {
    // Variables for data
    MeasurementPackage boilerTemp;
    MeasurementPackage extGasTemp;
    MeasurementPackage circulationPump;
    MeasurementPackage ExtFan;

    // h for short
    HAL_interface* h = HAL_instance;

    // Measure Boiler Temp
    double meas;
    h->measureBoilerTemp(meas);
    boilerTemp.timestamp_ = QDateTime::currentDateTime();
    boilerTemp.raw_measurements_.append(meas);
    boilerTemp.sensor_type_ = MeasurementPackage::SensorType::TEMP_PT100;
    boilerTemp.sensor_location = MeasurementPackage::SensorLocation::Boiler;
    emit measuredBoilerTemp(boilerTemp);

    // Measure ExtGas Temp
    h->measureExtGasTemp(meas);
    extGasTemp.timestamp_ = QDateTime::currentDateTime();
    extGasTemp.raw_measurements_.append(meas);
    extGasTemp.sensor_type_ = MeasurementPackage::SensorType::TEMP_PT100;
    extGasTemp.sensor_location = MeasurementPackage::SensorLocation::ExtGas;
    emit measuredExtGasTemp(extGasTemp);

    // Get Circulation Pump State
    bool pump;
    h->getCirculationPump(pump);
    circulationPump.timestamp_ = QDateTime::currentDateTime();
    circulationPump.raw_measurements_.append(pump);
    circulationPump.sensor_type_ = MeasurementPackage::SensorType::BOOLEAN;
    circulationPump.sensor_location = MeasurementPackage::SensorLocation::CircPump;
    emit changedCirculationPumpState(circulationPump);

    // Get ExtFan Speed
    h->getExtFanSpeed(meas);
    ExtFan.timestamp_ = QDateTime::currentDateTime();
    ExtFan.raw_measurements_.append(meas);
    ExtFan.sensor_type_ = MeasurementPackage::SensorType::PERCENTAGE;
    ExtFan.sensor_location = MeasurementPackage::SensorLocation::ExtFan;
    emit changedExtFanSpeed(ExtFan);
  }
}

/**
 * @brief HAL::startUpdates
 * This method starts the automatic updates. Internally it is using QObject's
 * startTimer() to start frequent timer updates and it'll launch timerEvent()
 * which then will call updateValues() method.
 *
 * In order this to work event loop must be running.
 * I.e default QThread or Qapplication is needed.
 *
 * @param period update period in seconds
 * @return HALError
 */
int HAL::startUpdates(const double period)
{
  period_ms = period * 1000;

  // Here we check is timer already running and that it can be started
  // If can't then return corresponding error codes
  if (!m_timerid) {  // m_timerid != 0 --> timer is already running
    m_timerid = startTimer(period_ms);
    if (m_timerid) {
      return HALErrors::NoError;
    }
    else {
        return HALErrors::CantStartTimer;
    }
    // END INNER IF
  }
  else {
    return HALErrors::TimerAlreadyRunning;
  }
  // END OUTER IF
  return HALErrors::UnknownError;
}

void HAL::stopUpdates()
{
  if (m_timerid) {
    // Timer will launch timerEvent() method as default
    //disconnect(this, SIGNAL(timeout()), this, SLOT(updateValues()));
    killTimer(m_timerid);
    m_timerid = 0;
  }
}
