#ifndef HAL_H
#define HAL_H

#include <QString>
#include <string>
#include <QMutex>
#include <QThread>
#include <QTimer>
#include <QDebug>

#include "hal_interface.h"
#include "measurement_package.h"

class HAL : public QObject
{
Q_OBJECT

public:
  explicit HAL(QObject *parent = Q_NULLPTR);
  ~HAL();
  QString getHWType();
  int init();
  HAL_interface* HALinstance() { return this->HAL_instance; }
  int setHWType(QString hwtype);
  int startUpdates(const double period=1);  // time in seconds
  void stopUpdates();


//  enum DataValues {
//    BoilerTemp,
//    ExtGasTemp,
//    ExtFan,
//    CirculationPump
//  };

signals:
  void measuredBoilerTemp(MeasurementPackage meas);
  void measuredExtGasTemp(MeasurementPackage meas);
  void changedCirculationPumpState(MeasurementPackage meas);
  void changedExtFanSpeed(MeasurementPackage meas);

public slots:
  void setCirculationPump(const bool state);
  void setExtFanSpeed(const double value);
  void updateValues();


private:
  // Store pointer to device specific HAL
  HAL_interface* HAL_instance = nullptr;
  // Keep information of hardware type
  QString hwType;
  // Period between measurements (valueUpdate)
  int period_ms;
  // Timer ID of the timer which handles frequent measurements
  int m_timerid=0;

protected:
  // when timerEvent() is launched by timer we just call updateValues
  // in order to go through measurement cycle
  void timerEvent(QTimerEvent *event) {Q_UNUSED(event); updateValues();}
};

enum HALErrors {
  NoError = 0,
  AlreadyInitialized,
  HWTypeNotSet,
  HWTypeNotRecognized,
  UnknownError,
  HALNotInitialized,
  TimerAlreadyRunning,
  CantStartTimer
};

#endif // HAL_H
